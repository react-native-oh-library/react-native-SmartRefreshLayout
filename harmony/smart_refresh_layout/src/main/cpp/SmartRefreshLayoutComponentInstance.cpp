#include "SmartRefreshLayoutComponentInstance.h"
#include <folly/dynamic.h>
#include "RNOH/arkui/ArkUINode.h"
#include "RNOH/arkui/ScrollNode.h"
#include "RNOHCorePackage/ComponentInstances/ScrollViewComponentInstance.h"
#include "react/renderer/graphics/Color.h"
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_gesture.h>
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

    SmartRefreshLayoutComponentInstance::SmartRefreshLayoutComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {

        m_pullToRefreshNode.insertChild(m_headerStackNode, 0);
        m_pullToRefreshNode.insertChild(m_listStackNode, 1);
        m_pullToRefreshNode.setPullToRefreshNodeDelegate(this);
    
        ArkUI_NumberValue clipValue[] = {{.u32 = 1}};
        ArkUI_AttributeItem clipItem = {clipValue, sizeof(clipValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_headerStackNode.getArkUINodeHandle(), NODE_CLIP, &clipItem);

        panGesture(m_pullToRefreshNode.getArkUINodeHandle());
    }


    void SmartRefreshLayoutComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                              std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        if (!isHeaderInserted) {
            m_headerStackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);

            isHeaderInserted = true;
        } else {
            m_listStackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
        }
        auto nodeValue =
            NativeNodeApi::getInstance()->getAttribute(m_pullToRefreshNode.getArkUINodeHandle(), NODE_WIDTH);
        m_headerStackNode.setSize(facebook::react::Size({nodeValue->value[nodeValue->size - 1].f32, 0}));
    }

    void SmartRefreshLayoutComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_headerStackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
        m_listStackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    PullToRefreshNode &SmartRefreshLayoutComponentInstance::getLocalRootArkUINode() { return m_pullToRefreshNode; }

    void SmartRefreshLayoutComponentInstance::panGesture(ArkUI_NodeHandle arkUI_NodeHandle) {
        auto gestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1 *>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_GESTURE, 1));
        auto panGesture = gestureApi->createPanGesture(1, GESTURE_DIRECTION_VERTICAL, 5);
        auto onPanActionCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {
            SmartRefreshLayoutComponentInstance *instance = (SmartRefreshLayoutComponentInstance *)extraParam;
            if (!instance->m_pullToRefreshNode.getPullToRefreshConfigurator().getHasRefresh() ||
                !instance->isComponentTop()) {
                return;
            }
            ArkUI_GestureEventActionType actionType = OH_ArkUI_GestureEvent_GetActionType(event);
            if (actionType == GESTURE_EVENT_ACTION_ACCEPT) {
                instance->offsetY = 0;
                instance->downY = OH_ArkUI_PanGesture_GetOffsetY(event);
                instance->touchYOld = instance->offsetY;
            } else if (actionType == GESTURE_EVENT_ACTION_UPDATE) {
                instance->offsetY = OH_ArkUI_PanGesture_GetOffsetY(event) - instance->downY;
                if (instance->offsetY >= 0) {
                    instance->onActionUpdate();
                } else {
                    instance->onActionEnd();
                }
            } else if (actionType == GESTURE_EVENT_ACTION_END) {
                instance->onActionEnd();
            }
        };
        gestureApi->setGestureEventTarget(
            panGesture, GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE | GESTURE_EVENT_ACTION_END, this,
            onPanActionCallBack);
        gestureApi->addGestureToNode(arkUI_NodeHandle, panGesture, PARALLEL, NORMAL_GESTURE_MASK);
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
            if (c->getComponentName() == "ScrollView") {
                auto scrollView = std::dynamic_pointer_cast<rnoh::ScrollViewComponentInstance>(c);
                if (scrollView != nullptr) {
                    return scrollView->getScrollViewMetrics().contentOffset.y <= 0;
                }
            }
        }
        return false;
    };


    void SmartRefreshLayoutComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        if (props == nullptr) {
            return;
        }
        // TODO: props attributes
        headerHeight = props->headerHeight;
        autoRefresh.refresh = props->autoRefresh.refresh;
        autoRefresh.time = props->autoRefresh.time;
        dragRate = props->dragRate;
        maxDragRate = props->maxDragRate;
        overScrollBounce = props->overScrollBounce;
        overScrollDrag = props->overScrollDrag;
        pureScroll = props->pureScroll;
        facebook::react::SharedColor headerColor = props->primaryColor;
        m_pullToRefreshNode.setEnableRefresh(props->enableRefresh);
        m_pullToRefreshNode.setMaxTranslate(props->headerHeight * 2);
        m_pullToRefreshNode.setHeaderBackgroundColor(headerColor);
    }


    void SmartRefreshLayoutComponentInstance::onRefresh() { m_eventEmitter->onRefresh({}); };

    void SmartRefreshLayoutComponentInstance::onHeaderPulling(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_eventEmitter->onHeaderPulling({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::onHeaderReleasing(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_eventEmitter->onHeaderReleasing({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::onHeaderMoving(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_eventEmitter->onHeaderMoving({percent, displayedHeaderHeight, headerHeight});
    };
    void SmartRefreshLayoutComponentInstance::onPullDownToRefresh() { m_eventEmitter->onPullDownToRefresh({}); };
    void SmartRefreshLayoutComponentInstance::onReleaseToRefresh() { m_eventEmitter->onReleaseToRefresh({}); };
    void SmartRefreshLayoutComponentInstance::onHeaderReleased() { m_eventEmitter->onHeaderReleased({}); }
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
