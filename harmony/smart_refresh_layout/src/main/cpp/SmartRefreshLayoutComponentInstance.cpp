#include "SmartRefreshLayoutComponentInstance.h"
#include <folly/dynamic.h>
#include <bits/alltypes.h>
#include "RNOH/arkui/ArkUINode.h"
#include "RNOHCorePackage/ComponentInstances/ScrollViewComponentInstance.h"
#include "TaskProcessor.h"
#include "react/renderer/graphics/Color.h"
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_gesture.h>
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNCDefaultHeaderComponentInstance.h"
#include <react/renderer/graphics/Geometry.h>

namespace rnoh {

    SmartRefreshLayoutComponentInstance::SmartRefreshLayoutComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {

        m_pullToRefreshNode.insertChild(m_headerStackNode, 0);
        m_pullToRefreshNode.insertChild(m_listStackNode, 1);
        m_headerStackNode.setAlign(ARKUI_ALIGNMENT_BOTTOM);
        m_headerStackNode.setAlignment(ARKUI_ALIGNMENT_BOTTOM);
        m_pullToRefreshNode.setPullToRefreshNodeDelegate(this);

        ArkUI_NumberValue clipValue[] = {{.u32 = 1}};
        ArkUI_AttributeItem clipItem = {clipValue, sizeof(clipValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_headerStackNode.getArkUINodeHandle(), NODE_CLIP, &clipItem);
        panGesture(m_pullToRefreshNode.getArkUINodeHandle());
        NativeNodeApi::getInstance()->registerNodeEvent(m_pullToRefreshNode.getArkUINodeHandle(), NODE_EVENT_ON_APPEAR,
                                                        NODE_EVENT_ON_APPEAR, this);
    }

    void SmartRefreshLayoutComponentInstance::onAppArea() {
        if (this->autoRefresh.refresh) {
            int32_t delayTime = (int32_t)autoRefresh.time;
            if (delayTime > 0) {
                TaskProcessor *taskProcessor = new TaskProcessor();
                taskProcessor->startDelayTask(static_cast<std::chrono::milliseconds>(delayTime), [this]() {
                    auto instance = std::static_pointer_cast<RNInstanceInternal>(m_deps->rnInstance.lock());
                    if (!instance) {
                        return;
                    }
                    instance->getTaskExecutor()->runTask(
                        TaskThread::MAIN, [wptr = this->weak_from_this(), wInstance = instance->weak_from_this()] {
                            auto ptr = std::static_pointer_cast<SmartRefreshLayoutComponentInstance>(wptr.lock());
                            if (ptr) {
                                ptr->trYTop = ptr->headerHeight * 2;
                                ptr->onActionEnd();
                            }
                        });
                });
            } else {
                this->trYTop = this->headerHeight * 2;
                this->onActionEnd();
            }
        }
    };

    void SmartRefreshLayoutComponentInstance::finalizeUpdates() {
        setHeaderChildSize();
    }  

    void SmartRefreshLayoutComponentInstance::setHeaderChildSize(){
        if (mWidth != getLayoutMetrics().frame.size.width) {
            mWidth = getLayoutMetrics().frame.size.width;
        }
        setNodeWidth(packageHeaderNode,mWidth);
        setNodeWidth(m_headerStackNode,mWidth);
    }

    void SmartRefreshLayoutComponentInstance::setNodeWidth(ArkUINode &arkUINode,float width) {
        ArkUI_NumberValue widthValue[] = { width };
        ArkUI_AttributeItem widthItem = {widthValue, sizeof(widthValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(arkUINode.getArkUINodeHandle(), NODE_WIDTH, &widthItem);
    }

    void SmartRefreshLayoutComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                              std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
         
        mWidth = childComponentInstance->getLayoutMetrics().frame.size.width;
        if (!isHeaderInserted) {
            packageHeaderNode.insertChild(childComponentInstance->getLocalRootArkUINode(), 0);
            m_headerStackNode.insertChild(packageHeaderNode, index);
            isHeaderInserted = true;
        } else {
            m_listStackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
        }
    
        m_headerStackNode.setSize(facebook::react::Size({mWidth, 0}));
        setOtherHeaderDelegate();
    }

    void SmartRefreshLayoutComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_headerStackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
        m_listStackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };


    PullToRefreshNode &SmartRefreshLayoutComponentInstance::getLocalRootArkUINode() { return m_pullToRefreshNode; }

    void SmartRefreshLayoutComponentInstance::panGesture(ArkUI_NodeHandle arkUI_NodeHandle) {
        auto anyGestureApi = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1");
        auto gestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1 *>(anyGestureApi);
        auto panGesture = gestureApi->createPanGesture(1, GESTURE_DIRECTION_VERTICAL, 0.1);
        auto onPanActionCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {
            SmartRefreshLayoutComponentInstance *instance = (SmartRefreshLayoutComponentInstance *)extraParam;
            if (!instance->m_pullToRefreshNode.getPullToRefreshConfigurator().getHasRefresh()) {
                return;
            }
            ArkUI_GestureEventActionType actionType = OH_ArkUI_GestureEvent_GetActionType(event);
            if (actionType == GESTURE_EVENT_ACTION_ACCEPT) {
                instance->offsetY = 0;
                instance->downY = OH_ArkUI_PanGesture_GetOffsetY(event);
                instance->touchYOld = instance->offsetY;
                instance->onPullDownToRefresh();
            } else if (actionType == GESTURE_EVENT_ACTION_UPDATE) {
                instance->offsetY = OH_ArkUI_PanGesture_GetOffsetY(event) - instance->downY;
                if (instance->offsetY >= 0) {
                    instance->onActionUpdate();
                }
            } else if (actionType == GESTURE_EVENT_ACTION_END) {
                instance->onActionEnd();
                instance->onHeaderReleased();
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
                    setPullHeaderHeight(trYTop);
                    if (trYTop / maxTranslate < 0.5) {
                        state = IS_PULL_DOWN_1;
                    } else {
                        state = IS_PULL_DOWN_2;
                        // 可释放刷新时触发
                        this->onReleaseToRefresh();
                    }
                    if (trYTop >= 0) {
                        this->changeStatus();
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
                    setPullHeaderHeight(trYTop);
                    this->changeStatus();
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
        animation->SetAnimationParams(
            static_cast<std::chrono::milliseconds>(duration), start, target, [this, &target](double value) {
                trYTop = value < 0 ? 0 : value;
                auto instance = std::static_pointer_cast<RNInstanceInternal>(m_deps->rnInstance.lock());
                if (!instance) {
                    return;
                }
                instance->getTaskExecutor()->runTask(
                    TaskThread::MAIN, [wptr = this->weak_from_this(), wInstance = instance->weak_from_this()] {
                        auto ptr = std::static_pointer_cast<SmartRefreshLayoutComponentInstance>(wptr.lock());
                        if (ptr) {
                            ptr->setPullHeaderHeight(ptr->trYTop);
                            if (ptr->trYTop == 0) {
                                ptr->state = IS_FREE;
                                ptr->m_pullToRefreshNode.markDirty();
                                ptr->changeStatus();
                            }
                        }
                    });
            });
        if (animation->GetAnimationStatus() == ANIMATION_FREE || animation->GetAnimationStatus() == ANIMATION_FINISH) {
            animation->Start();
        }
    }

    void SmartRefreshLayoutComponentInstance::finishRefresh() {
        state = IS_REFRESHED;
        changeStatus();
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
    void SmartRefreshLayoutComponentInstance::onNativeResponderBlockChange(bool blocked) {
        std::vector<ComponentInstance::Shared> child = getChildren();
        for (ComponentInstance::Shared c : child) {
            if (c->getComponentName() == "ScrollView") {
                auto scrollView = std::dynamic_pointer_cast<rnoh::ScrollViewComponentInstance>(c);
                if (blocked) {
                    scrollView->setNativeResponderBlocked(!blocked,"REACT_NATIVE");
                }
                break;
            }
        }
    }

    void SmartRefreshLayoutComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        if (props == nullptr) {
            return;
        }
        headerHeight = props->headerHeight;
        autoRefresh.refresh = props->autoRefresh.refresh;
        autoRefresh.time = props->autoRefresh.time;
        dragRate = props->dragRate;
        maxDragRate = props->maxDragRate;
        overScrollBounce = props->overScrollBounce;
        overScrollDrag = props->overScrollDrag;
        pureScroll = props->pureScroll;
        mHeaderBackgroundColor = props->primaryColor;
        if (delegate != nullptr && (*(delegate->GetPrimaryColor())) != -1) {
            mHeaderBackgroundColor = delegate->GetPrimaryColor();
        }

        m_pullToRefreshNode.setHeaderBackgroundColor(mHeaderBackgroundColor);
        m_pullToRefreshNode.setEnableRefresh(props->enableRefresh);
        m_pullToRefreshNode.setMaxTranslate(props->headerHeight * (maxDragRate != 2 ? maxDragRate : 2));
        m_pullToRefreshNode.setSensitivity(dragRate != 0.5 ? dragRate : 0.5);
    }


    void SmartRefreshLayoutComponentInstance::onRefresh() { m_eventEmitter->onRefresh({}); };

    void SmartRefreshLayoutComponentInstance::setPullHeaderHeight(float h) {

        if (globalHeaderType == "RNCMaterialHeader" &&delegate) {
            delegate->onHeaderMove(h);
        } else {
            m_pullToRefreshNode.setHeaderHeight(h);
        }
        // 下拉中
        if (oldHeaderTop < h) {
            onHeaderPulling(h);
        } else if (oldHeaderTop > h) {
            onHeaderReleasing(h);
        }
        oldHeaderTop = h;
    }

    void SmartRefreshLayoutComponentInstance::onHeaderPulling(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_eventEmitter->onHeaderPulling({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::changeStatus() {
        if (globalHeaderType != "RNCDefaultHeader" && globalHeaderType != "RNCClassicsHeader" &&
            globalHeaderType != "RNCMaterialHeader") {
            return;
        }
        if (delegate == nullptr) {
            setOtherHeaderDelegate();
        } else {
            delegate->onRefreshStatusChange(state);
        }
    }


    void SmartRefreshLayoutComponentInstance::setOtherHeaderDelegate() {
        if (delegate == nullptr) {
            std::vector<ComponentInstance::Shared> child = getChildren();
            for (ComponentInstance::Shared c : child) {
                if (c->getComponentName() == "RNCDefaultHeader" || c->getComponentName() == "RNCClassicsHeader" ||
                    c->getComponentName() == "RNCMaterialHeader" || c->getComponentName() == "RNCAnyHeader") {
                    delegate = std::dynamic_pointer_cast<rnoh::HeaderNodeDelegate>(c);
                    if (delegate != nullptr && c->getComponentName() == "RNCMaterialHeader") {
                        ArkUI_NumberValue clipValue[] = {{.u32 = 1}};
                        ArkUI_AttributeItem clipItem = {clipValue, sizeof(clipValue) / sizeof(ArkUI_NumberValue)};
                        NativeNodeApi::getInstance()->setAttribute(m_pullToRefreshNode.getArkUINodeHandle(), NODE_CLIP,
                                                                   &clipItem);
                        delegate->addHeader(mWidth, 3, &m_pullToRefreshNode);
                    }
                    if (delegate != nullptr && (*(delegate->GetPrimaryColor())) != -1) {
                        mHeaderBackgroundColor = delegate->GetPrimaryColor();
                    }
                    break;
                }
            }
        }
        m_pullToRefreshNode.setHeaderBackgroundColor(mHeaderBackgroundColor);
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
