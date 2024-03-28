#include "SmartRefreshLayoutComponentInstance.h"
#include <folly/dynamic.h>
#include "RNOH/arkui/ArkUINode.h"
#include "RNOH/arkui/ScrollNode.h"
#include "RNOHCorePackage/ComponentInstances/ScrollViewComponentInstance.h"
#include "react/renderer/graphics/Color.h"
// #include <arkui/native_interface.h>
// #include <arkui/native_node.h>
// #include <arkui/native_gesture.h>
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

    SmartRefreshLayoutComponentInstance::SmartRefreshLayoutComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {

        m_pullToRefreshNode.insertChild(m_headerStackNode, 0);
        m_pullToRefreshNode.insertChild(m_listStackNode, 1);
        m_pullToRefreshNode.setPullToRefreshNodeDelegate(this);
        m_headerStackNode.setHeight(facebook::react::Size({0, 0}));

        ArkUI_NumberValue clipValue[] = {{.u32 = 1}};
        ArkUI_AttributeItem clipItem = {clipValue, sizeof(clipValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_headerStackNode.getArkUINodeHandle(), NODE_CLIP, &clipItem);


        ArkUINodeRegistry::getInstance().registerTouchHandler(&m_pullToRefreshNode, this);
        NativeNodeApi::getInstance()->registerNodeEvent(m_pullToRefreshNode.getArkUINodeHandle(), NODE_TOUCH_EVENT, 0);

        //         panGesture(m_pullToRefreshNode.getArkUINodeHandle());
    }


    void SmartRefreshLayoutComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                          std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        if (!isHeaderInserted) {
            m_headerStackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);

            isHeaderInserted = true;
        } else {
            m_listStackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
        }
    }

    void SmartRefreshLayoutComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_headerStackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
        m_listStackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    PullToRefreshNode &SmartRefreshLayoutComponentInstance::getLocalRootArkUINode() { return m_pullToRefreshNode; }

    void SmartRefreshLayoutComponentInstance::onTouchEvent(ArkUI_NodeTouchEvent e) {
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::onTouchEvent> nodeY :" << e.actionTouch.nodeY
                  << "; action:" << e.action;
        if (!m_pullToRefreshNode.getPullToRefreshConfigurator().getHasRefresh()) {
            return;
        }
        if (e.action == ArkUI_NodeTouchEventAction::NODE_ACTION_CANCEL) {
        
        } else if (e.action == ArkUI_NodeTouchEventAction::NODE_ACTION_DOWN) {
            if (m_pullToRefreshNode.getPullToRefreshConfigurator().getHasRefresh()) {
                onPullDownToRefresh();
            }
            offsetY = 0;
            downY = e.actionTouch.nodeY;
            this->touchYOld = offsetY;
        } else if (e.action == ArkUI_NodeTouchEventAction::NODE_ACTION_MOVE) {
            offsetY = e.actionTouch.nodeY - downY;
            LOG(INFO) << "[clx] <PullToRefreshNode::onNodeEvent > offsetY: " << offsetY;
            if (offsetY > 0) {
                this->onActionUpdate();
            } else {
                this->onActionEnd();
            }
        } else if (e.action == ArkUI_NodeTouchEventAction::NODE_ACTION_UP) {
            LOG(INFO) << "[clx] <PullToRefreshNode::onNodeEvent > NODE_ACTION_CANCEL";
            this->onActionEnd();
        }
    }


    void SmartRefreshLayoutComponentInstance::onActionUpdate() {
        if (state == IS_FREE || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2 || state == IS_PULL_UP_1 ||
            state == IS_PULL_UP_2) {
            auto maxTranslate = m_pullToRefreshNode.getPullToRefreshConfigurator().getMaxTranslate();
            auto loadImgHeight = m_pullToRefreshNode.getPullToRefreshConfigurator().getLoadImgHeight();
            auto refreshHeight = m_pullToRefreshNode.getPullToRefreshConfigurator().getRefreshHeight();
            touchYNew = offsetY;
            if (!isComponentTop()) {
                return;
            }
            auto isPullAction = (touchYNew - touchYOld) > 0;
            if ((state == IS_FREE && isPullAction) || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2) {
                if (m_pullToRefreshNode.getPullToRefreshConfigurator().getHasRefresh()) {
                    // 获取最新位移距离
                    float trY = touchYNew - touchYOld;
                    // 计算当前需要位移的距离
                    trYTop = this->getTranslateYOfRefresh(trY);
                    m_pullToRefreshNode.setHeaderHeight(trYTop);
                    if (trY < refreshHeight) {
                        state = IS_PULL_DOWN_1;
                    } else {
                        state = IS_PULL_DOWN_2;
                    }
                    if (trY > 0) {
                        this->onHeaderPulling(trYTop);
                    }
                }
            }
            touchYOld = touchYNew;
        }
    }

    void SmartRefreshLayoutComponentInstance::onActionEnd() {
        auto maxTranslate = m_pullToRefreshNode.getPullToRefreshConfigurator().getMaxTranslate();
        auto refreshAnimDuration = m_pullToRefreshNode.getPullToRefreshConfigurator().getRefreshAnimDuration();
        if (trYTop > 0) {
            if (state == IS_FREE || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2) {
                if (trYTop / maxTranslate < 0.5) {
                    closeRefresh(trYTop, 0, m_pullToRefreshNode.getPullToRefreshConfigurator().getAnimDuration());
                } else {
                    state = IS_REFRESHING;
                    trYTop = maxTranslate * 0.5; // 这个位置要设置高度，收回去
                    this->onRefresh();
                    m_pullToRefreshNode.setHeaderHeight(trYTop);
                }
            }
        }
    }
    float SmartRefreshLayoutComponentInstance::getTranslateYOfRefresh(float newTranslateY) {
        auto config = m_pullToRefreshNode.getPullToRefreshConfigurator();
        if (&config != nullptr) {
            facebook::react::Float maxTranslateY = config.getMaxTranslate();
            facebook::react::Float sensitivity = config.getSensitivity();
            //             if (maxTranslateY != 0.0 && sensitivity != 0.0 && trYTop != 0.0) {
            // 阻尼值计算
            facebook::react::Float dampingFactor;
            if ((trYTop / maxTranslateY) < 0.2) {
                dampingFactor = 1.0;
            } else if ((trYTop / maxTranslateY) < 0.4) {
                dampingFactor = 0.8;
            } else if ((trYTop / maxTranslateY) < 0.6) {
                dampingFactor = 0.6;
            } else if ((trYTop / maxTranslateY) < 0.8) {
                dampingFactor = 0.4;
            } else {
                dampingFactor = 0.2;
            }
            newTranslateY = newTranslateY * dampingFactor * sensitivity;
            // 下拉值计算
            facebook::react::Float newTotalTranslateY = trYTop + newTranslateY;
            if (newTotalTranslateY > maxTranslateY) {
                return maxTranslateY;
            } else if (newTotalTranslateY < 0) {
                return 0;
            } else {
                return newTotalTranslateY;
            }
        }
        //         }
        return 0;
    }

    void SmartRefreshLayoutComponentInstance::closeRefresh(float start, float target, int32_t duration) {
        if (trYTop == target) {
            return;
        }
        if (animation != nullptr &&
            (animation->GetAnimationStatus() == ANIMATION_START || animation->GetAnimationStatus() == ANIMATION_RUN)) {
            return;
        }
        if (animation == nullptr) {
            animation = new Animation();
        }
        animation->SetAnimationParams(static_cast<std::chrono::milliseconds>(duration), start, target,
                                      [this, &target](double value) {
                                          trYTop = value < 0 ? 0 : value;
                                          m_pullToRefreshNode.setHeaderHeight(trYTop);
                                          if (trYTop == 0) {
                                              state = IS_FREE;
                                              m_pullToRefreshNode.markDirty();
                                          }
                                      });
        if (animation->GetAnimationStatus() == ANIMATION_FREE || animation->GetAnimationStatus() == ANIMATION_FINISH) {
            animation->Start();
        }
    }

    void SmartRefreshLayoutComponentInstance::finishRefresh() {
        state = IS_REFRESHED;
        closeRefresh(trYTop, 0, m_pullToRefreshNode.getPullToRefreshConfigurator().getAnimDuration());
    }

    bool SmartRefreshLayoutComponentInstance::isComponentTop() {
        std::vector<ComponentInstance::Shared> child = getChildren();
        for (ComponentInstance::Shared c : child) {
            if (c->getContext().componentName == "ScrollView") {
                auto scrollView = std::dynamic_pointer_cast<rnoh::ScrollViewComponentInstance>(c);
                if (scrollView != nullptr) {
                    return scrollView->getScrollViewMetrics().contentOffset.y <= 0;
                }
            }
        }
        return false;
    };

    void SmartRefreshLayoutComponentInstance::setNativeResponderBlocked(bool blocked) {
        std::vector<ComponentInstance::Shared> child = getChildren();
        for (ComponentInstance::Shared c : child) {
            if (c->getContext().componentName == "ScrollView") {
                auto scrollView = std::dynamic_pointer_cast<rnoh::ScrollViewComponentInstance>(c);
                if (blocked) {
                    scrollView->setNativeResponderBlocked(!blocked);
                    break;
                }
            }
        }
    }
    void SmartRefreshLayoutComponentInstance::setProps(facebook::react::Props::Shared props) {
        ComponentInstance::setProps(props);
        auto refreshProps = std::dynamic_pointer_cast<const facebook::react::SmartRefreshLayoutProps>(props);
        if (refreshProps == nullptr) {
            return;
        }
        // TODO: refreshProps attributes
        headerHeight = refreshProps->headerHeight;
        autoRefresh.refresh = refreshProps->autoRefresh.refresh;
        autoRefresh.time = refreshProps->autoRefresh.time;
        dragRate = refreshProps->dragRate;
        maxDragRate = refreshProps->maxDragRate;
        overScrollBounce = refreshProps->overScrollBounce;
        overScrollDrag = refreshProps->overScrollDrag;
        pureScroll = refreshProps->pureScroll;
        facebook::react::SharedColor headerColor = refreshProps->primaryColor;
        m_pullToRefreshNode.setEnableRefresh(refreshProps->enableRefresh);
        m_pullToRefreshNode.setMaxTranslate(refreshProps->headerHeight * 2);
        m_pullToRefreshNode.setHeaderBackgroundColor(headerColor);
    }

    void SmartRefreshLayoutComponentInstance::setEventEmitter(facebook::react::SharedEventEmitter eventEmitter) {
        ComponentInstance::setEventEmitter(eventEmitter);
        auto smartRefreshLayoutEventEmitter =
            std::dynamic_pointer_cast<const facebook::react::SmartRefreshLayoutEventEmitter>(eventEmitter);
        if (smartRefreshLayoutEventEmitter == nullptr) {
            return;
        }
        m_smartRefreshLayoutEventEmitter = smartRefreshLayoutEventEmitter;
    };

    void SmartRefreshLayoutComponentInstance::onRefresh() { m_smartRefreshLayoutEventEmitter->onRefresh({}); };

    void SmartRefreshLayoutComponentInstance::onHeaderPulling(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_smartRefreshLayoutEventEmitter->onHeaderPulling({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::onHeaderReleasing(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_smartRefreshLayoutEventEmitter->onHeaderReleasing({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::onHeaderMoving(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_smartRefreshLayoutEventEmitter->onHeaderMoving({percent, displayedHeaderHeight, headerHeight});
    };
    void SmartRefreshLayoutComponentInstance::onPullDownToRefresh() {
        m_smartRefreshLayoutEventEmitter->onPullDownToRefresh({});
    };
    void SmartRefreshLayoutComponentInstance::onReleaseToRefresh() {
        m_smartRefreshLayoutEventEmitter->onReleaseToRefresh({});
    };
    void SmartRefreshLayoutComponentInstance::onHeaderReleased() {
        m_smartRefreshLayoutEventEmitter->onHeaderReleased({});
    }
    void SmartRefreshLayoutComponentInstance::handleCommand(std::string const &commandName,
                                                            folly::dynamic const &args) {
        if (commandName == "finishRefresh" && args.isArray() && args.size() == 2) {
            auto delayed = args[0];
            auto success = args[1];
            if (delayed != INFINITY) {
                if (delayed >= 0) {
                    m_pullToRefreshNode.getPullToRefreshConfigurator().setFinishDelay(delayed.asInt());
                } else {
                    m_pullToRefreshNode.getPullToRefreshConfigurator().setFinishDelay(0);
                }
            } else {
                m_pullToRefreshNode.getPullToRefreshConfigurator().setFinishDelay(500);
            }
            finishRefresh();
        }
    };

} // namespace rnoh
