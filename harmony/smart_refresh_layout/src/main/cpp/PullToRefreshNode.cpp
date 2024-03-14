#include "PullToRefreshNode.h"
#include <bits/alltypes.h>
#include <glog/logging.h>
#include <linux/pkt_sched.h>
#include <sys/stat.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <future>

namespace rnoh {
    PullToRefreshNode::PullToRefreshNode()
        : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_COLUMN)),
          m_headerArkUINodeHandle(nullptr), m_listArkUINodeHandle(nullptr), m_pullToRefreshNodeDelegate(nullptr) {

        maybeThrow(NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, NODE_TOUCH_EVENT, 0));
        ArkUI_NumberValue columnFlexValue[] = {{.i32 = ARKUI_FLEX_ALIGNMENT_CENTER}};
        ArkUI_AttributeItem columnFlexItem = {columnFlexValue, sizeof(columnFlexValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_COLUMN_JUSTIFY_CONTENT, &columnFlexItem);

        m_headerArkUINodeHandle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK);
        auto columnHandle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_COLUMN);
        m_listArkUINodeHandle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK);

        uint32_t colorValue1 = 0xFF56aa1D;
        ArkUI_NumberValue preparedColorValue1[] = {{.u32 = colorValue1}};
        ArkUI_AttributeItem colorItem1 = {preparedColorValue1, sizeof(preparedColorValue1) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_listArkUINodeHandle, NODE_BACKGROUND_COLOR, &colorItem1);

        ArkUI_NumberValue clipValues[] = {true};
        ArkUI_AttributeItem clipValue = {clipValues, 1};
        NativeNodeApi::getInstance()->setAttribute(m_listArkUINodeHandle, NODE_CLIP, &clipValue);


        ArkUI_NumberValue heightNumberValue[] = {static_cast<float>(trYTop)};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        LOG(INFO) << "[clx] <PullToRefreshNode::animateWithCubicBezier> AnimationCallBack111 cal: " << trYTop;
        NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_HEIGHT, &heightItem);

        //         uint32_t colorValue2 = 0xFF6495ED;
        //         ArkUI_NumberValue preparedColorValue2[] = {{.u32 = colorValue2}};
        //         ArkUI_AttributeItem colorItem2 = {preparedColorValue2, sizeof(preparedColorValue2) /
        //         sizeof(ArkUI_NumberValue)}; NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle,
        //         NODE_BACKGROUND_COLOR, &colorItem2);

        ArkUI_NumberValue alignments[] = {{.u32 = ARKUI_ALIGNMENT_BOTTOM}};
        ArkUI_AttributeItem alignment = {alignments, sizeof(alignments) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_STACK_ALIGN_CONTENT, &alignment);


        NativeNodeApi::getInstance()->addChild(m_nodeHandle, m_headerArkUINodeHandle);
        NativeNodeApi::getInstance()->addChild(columnHandle, m_listArkUINodeHandle);
        NativeNodeApi::getInstance()->addChild(m_nodeHandle, columnHandle);
    }

    PullToRefreshNode::~PullToRefreshNode() {
        NativeNodeApi::getInstance()->unregisterNodeEvent(m_nodeHandle, NODE_TOUCH_EVENT);
    }

    void PullToRefreshNode::setHeaderHeight(float h) { mHeight = h; }


    void PullToRefreshNode::onNodeEvent(ArkUI_NodeEvent *event) {
        LOG(INFO) << "[clx] <ssss11 PullToRefreshNode::onNodeEvent > ------kind: " << event->eventId;
        if (event->kind == ArkUI_NodeEventType::NODE_TOUCH_EVENT) {
            if (event->touchEvent.action == ArkUI_NodeTouchEventAction::NODE_ACTION_CANCEL) {
                offsetY = 0;
                downY = event->touchEvent.actionTouch.nodeY;
                this->touchYOld = offsetY;

            } else if (event->touchEvent.action == ArkUI_NodeTouchEventAction::NODE_ACTION_DOWN) {
                this->onActionEnd();
            } else if (event->touchEvent.action == ArkUI_NodeTouchEventAction::NODE_ACTION_MOVE) {
                offsetY = event->touchEvent.actionTouch.nodeY - downY;
                LOG(INFO) << "[clx] <PullToRefreshNode::onNodeEvent > offsetY: " << offsetY;
                if (offsetY > 0) {
                    this->onActionUpdate(event->touchEvent.actionTouch);
                } else {
                    this->onActionEnd();
                }
            } else if (event->touchEvent.action == ArkUI_NodeTouchEventAction::NODE_ACTION_UP) {
                LOG(INFO) << "[clx] <PullToRefreshNode::onNodeEvent > NODE_ACTION_CANCEL";
            }
        }
    };

    void PullToRefreshNode::setPullToRefreshNodeDelegate(PullToRefreshNodeDelegate *pullToRefreshNodeDelegate) {
        m_pullToRefreshNodeDelegate = pullToRefreshNodeDelegate;
    }

    void PullToRefreshNode::onActionUpdate(ArkUI_NodeTouchPoint const &event) {
        LOG(INFO) << "[clx] <PullToRefreshNode::onActionUpdate> state: " << state;
        if (state == IS_FREE || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2 || state == IS_PULL_UP_1 ||
            state == IS_PULL_UP_2) {
            LOG(INFO) << "[clx] <PullToRefreshNode::onActionUpdate> begin";
            auto maxTranslate = refreshConfigurator.getMaxTranslate();
            auto loadImgHeight = refreshConfigurator.getLoadImgHeight();
            auto refreshHeight = refreshConfigurator.getRefreshHeight();
            touchYNew = offsetY;

            // whether pan down
            auto isPullAction = (touchYNew - touchYOld) > 0;

            if ((state == IS_FREE && isPullAction) || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2) {
                if (refreshConfigurator.getHasRefresh()) {
                    // 获取最新位移距离
                    float trY = touchYNew - touchYOld;
                    LOG(INFO) << "[clx] <PullToRefreshNode::onActionUpdate> trY: " << trY;
                    // 计算当前需要位移的距离
                    trYTop = getTranslateYOfRefresh(trY);
                    ArkUI_NumberValue heightNumberValue[] = {trYTop};
                    ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
                    NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_HEIGHT, &heightItem);
                    if (trY < refreshHeight) {
                        state = IS_PULL_DOWN_1;
                    } else {
                        state = IS_PULL_DOWN_2;
                    }
                    // 如果没有自定义刷新动画，就执行内置动画下拉时的逻辑
                    if (!customRefresh && maxTranslate > 0) {
                    }
                    if (trY > 0) {
                        if (m_pullToRefreshNodeDelegate != nullptr) {
                            m_pullToRefreshNodeDelegate->onHeaderPulling(trYTop);
                        }
                    }
                }
            }
            touchYOld = touchYNew;
        }
    }

    void PullToRefreshNode::onActionEnd() {
        LOG(INFO) << "[clx] <PullToRefreshNode::onActionEnd> closeRefresh: " << trYTop;
        auto maxTranslate = refreshConfigurator.getMaxTranslate();
        auto refreshAnimDuration = refreshConfigurator.getRefreshAnimDuration();
        if (trYTop > 0) {
            if (state == IS_FREE || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2) {
                if (trYTop / maxTranslate < 0.5) {
                    closeRefresh();
                } else {
                    state = IS_REFRESHING;
                    trYTop = maxTranslate * 0.5; // 这个位置要设置高度，收回去
                    this->onRefresh();
                    LOG(INFO) << "[clx] <ssss11 PullToRefreshNode::onNodeEvent >onRefresh: ";
                    ArkUI_NumberValue heightNumberValue[] = {trYTop};
                    ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
                    NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_HEIGHT, &heightItem);
                    //                     state = IS_REFRESHED;
                    //                     closeRefresh();
                }
            }
        }
    }

    float PullToRefreshNode::getTranslateYOfRefresh(float newTranslateY) {
        if (&refreshConfigurator != nullptr) {
            facebook::react::Float maxTranslateY = refreshConfigurator.getMaxTranslate();
            facebook::react::Float sensitivity = refreshConfigurator.getSensitivity();
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
            LOG(INFO) << "[clx] <PullToRefreshNode::getTranslateYOfRefresh> newTranslateY: " << newTranslateY;
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
    void PullToRefreshNode::finishRefresh() {
        state = IS_REFRESHED;
        closeRefresh();
    }

    void PullToRefreshNode::closeRefresh() {
        if (animation != nullptr &&
            (animation->GetAnimationStatus() == ANIMATION_START || animation->GetAnimationStatus() == ANIMATION_RUN)) {
            LOG(INFO) << "[clx] <PullToRefreshNode::animateWithCubicBezier> closeRefresh return";
            return;
        }
        if (animation == nullptr) {
            animation = new Animation();
        }
        animation->SetAnimationParams(
            static_cast<std::chrono::milliseconds>(refreshConfigurator.getAnimDuration()), trYTop, 0,
            [this](double value) {
                //           if (state == IS_FREE || state == IS_PULL_DOWN_1 || state == IS_PULL_DOWN_2) {
                trYTop = value;
                LOG(INFO) << "[clx] <PullToRefreshNode::animateWithCubicBezier> AnimationCallBack3333 cal: " << trYTop
                          << ";value:" << value;
                ArkUI_NumberValue heightNumberValue[] = {trYTop};
                ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
                NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_HEIGHT, &heightItem);
                if (trYTop == 0) {
                    state = IS_FREE;
                    auto itemProps = NativeNodeApi::getInstance()->getAttribute(m_headerArkUINodeHandle, NODE_HEIGHT);
                    auto size = itemProps->size;
                    const ArkUI_NumberValue *value = itemProps->value;
                    auto pp = value[size - 1];
                    LOG(INFO) << "[clx] <PullToRefreshNode::animateWithCubicBezier> AnimationCallBack3333 size: "
                              << size << ";value:" << pp.f32;
                    //          }
                }
            });
        LOG(INFO) << "[clx] <PullToRefreshNode::animateWithCubicBezier> closeRefresh Start status "
                  << animation->GetAnimationStatus();
        if (animation->GetAnimationStatus() == ANIMATION_FREE || animation->GetAnimationStatus() == ANIMATION_FINISH) {
            animation->Start();
        }
    }

    void PullToRefreshNode::onRefresh() {
        if (m_pullToRefreshNodeDelegate != nullptr) {
            m_pullToRefreshNodeDelegate->onRefresh(); // onRefresh test
        }
    }

    void PullToRefreshNode::insertChild(ArkUINode &child, bool &isListInserted) {
        if (!isListInserted) {
            maybeThrow(NativeNodeApi::getInstance()->addChild(m_listArkUINodeHandle, child.getArkUINodeHandle()));
        } else {
            maybeThrow(NativeNodeApi::getInstance()->addChild(m_headerArkUINodeHandle, child.getArkUINodeHandle()));
        }
    }
    void PullToRefreshNode::insertHeaderChild(ArkUINode &child) {
        auto rn_headerHandle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK);
        maybeThrow(NativeNodeApi::getInstance()->addChild(rn_headerHandle, child.getArkUINodeHandle()));
        maybeThrow(NativeNodeApi::getInstance()->addChild(m_headerArkUINodeHandle, rn_headerHandle));
    }

    void PullToRefreshNode::setEnableRefresh(bool enable) { refreshConfigurator.setHasRefresh(enable); }
    void PullToRefreshNode::setMaxTranslate(float maxHeight) { refreshConfigurator.setMaxTranslate(maxHeight); }

    void PullToRefreshNode::removeChild(ArkUINode &child) {

        if (m_listArkUINodeHandle != nullptr) {
            NativeNodeApi::getInstance()->removeChild(m_listArkUINodeHandle, child.getArkUINodeHandle());
            m_listArkUINodeHandle = nullptr;
            return;
        }
        if (m_headerArkUINodeHandle != nullptr) {
            NativeNodeApi::getInstance()->removeChild(m_headerArkUINodeHandle, child.getArkUINodeHandle());
            m_headerArkUINodeHandle = nullptr;
        }
    }
} // namespace rnoh