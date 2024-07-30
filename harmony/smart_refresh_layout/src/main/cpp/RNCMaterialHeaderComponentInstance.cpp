//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCMaterialHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "TaskCommonThread.h"
#include "react/renderer/imagemanager/primitives.h"
#include "SmartRefreshState.h"
#include <bits/alltypes.h>

namespace rnoh {

    RNCMaterialHeaderComponentInstance::RNCMaterialHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}

    void RNCMaterialHeaderComponentInstance::addHeader(int32_t screenWidth, int32_t index, ArkUINode *arkUI_Node) {
        mWindowWidth = screenWidth;
        progressNode.setLoadingProgressNodeColor(0x53658461);
        progressNode.setLoadingProgressNodeAnimating(true);
        progressNode.setSize({45, 45});
    
        ArkUI_NumberValue heightArray[] = {{.f32 = 45}};
        ArkUI_AttributeItem heightValue[] = {heightArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_HEIGHT, heightValue);
        ArkUI_NumberValue widthArray[] = {{.f32 = 45}};
        ArkUI_AttributeItem widthValue[] = {widthArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_WIDTH, widthValue);

        ArkUI_NumberValue borderStyArray[] = {0.2};
        ArkUI_AttributeItem borderStyValue[] = {borderStyArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_BORDER_WIDTH, borderStyValue);

        ArkUI_NumberValue radiusArray[] = {{.f32 = 45}};
        ArkUI_AttributeItem radiusValue[] = {radiusArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_BORDER_RADIUS, radiusValue);
        imageStack.setBackgroundColor(0xFFfafafa);
        ArkUI_NumberValue borderColorArray[] = {
            {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}};
        ArkUI_AttributeItem borderColorValue[] = {borderColorArray, 4};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_BORDER_COLOR,
                                                   borderColorValue);

        uint32_t shadowColorValue = 0xffaaaaaa;
        uint32_t alpha = static_cast<uint32_t>((float)(shadowColorValue >> 24 & (0xff)) * 1.0);
        shadowColorValue = (alpha << 24) + (shadowColorValue & 0xffffff);
        ArkUI_NumberValue shadowValue[] = {
            {.f32 = 2}, {.i32 = 0}, {.f32 = 1}, {.f32 = 1}, {.i32 = 0}, {.u32 = shadowColorValue}, {.u32 = 0}};
        ArkUI_AttributeItem shadowItem = {.value = shadowValue,
                                          .size = sizeof(shadowValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_CUSTOM_SHADOW, &shadowItem);

        ArkUI_NumberValue z_indexArray[] = {{.f32 = 1000}};
        ArkUI_AttributeItem z_indexValue[] = {z_indexArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_Z_INDEX, z_indexValue);

        NativeNodeApi::getInstance()->insertChildAt(imageStack.getArkUINodeHandle(), progressNode.getArkUINodeHandle(),
                                                    0);
        NativeNodeApi::getInstance()->insertChildAt(arkUI_Node->getArkUINodeHandle(), imageStack.getArkUINodeHandle(),
                                                    index);
        ArkUI_NumberValue positionArray[] = {{.f32 = static_cast<float>((screenWidth - 46) / 2.0)}, {.f32 = -46}};
        ArkUI_AttributeItem positionValue[] = {positionArray, 2};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_POSITION, positionValue);
    }

    void RNCMaterialHeaderComponentInstance::onHeaderMove(float dur) {
        if (isRefreshed) {
            return;
        }
        ArkUI_NumberValue positionArray[] = {{.f32 = static_cast<float>((mWindowWidth - 46) / 2.0)}, {.f32 = dur - 46}};
        ArkUI_AttributeItem positionValue[] = {positionArray, 2};
        NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_POSITION, positionValue);
    }

    void RNCMaterialHeaderComponentInstance::setScaleAnimate(int32_t dur) {

        TaskCommonThread *task = new TaskCommonThread();
        task->setTaskParams(static_cast<std::chrono::milliseconds>(dur), [this](double v) {
            scaleSize = 1.0 - static_cast<float>(v);
            auto instance = std::static_pointer_cast<RNInstanceInternal>(m_deps->rnInstance.lock());
            if (!instance) {
                return;
            }
            instance->getTaskExecutor()->runTask(
                TaskThread::MAIN, [wptr = this->weak_from_this(), wInstance = instance->weak_from_this()] {
                    auto ptr = std::static_pointer_cast<RNCMaterialHeaderComponentInstance>(wptr.lock());
                    if (ptr) {
                        float value = ptr->scaleSize;
                        ArkUI_NumberValue scaleArray[] = {{.f32 = value}, {.f32 = value}};
                        ArkUI_AttributeItem scaleValue[] = {scaleArray, 2};
                        NativeNodeApi::getInstance()->setAttribute(ptr->imageStack.getArkUINodeHandle(), NODE_SCALE,
                                                                   scaleValue);
                        if (std::abs(value - 0.01) < 1e-6) {
                            ArkUI_NumberValue scaleArray[] = {{.f32 = 1.0}, {.f32 = 1.0}};
                            ArkUI_AttributeItem scaleValue[] = {scaleArray, 2};
                            NativeNodeApi::getInstance()->setAttribute(ptr->imageStack.getArkUINodeHandle(), NODE_SCALE,
                                                                       scaleValue);
                        }
                    }
                });
        });
        task->execute();
    }

    void RNCMaterialHeaderComponentInstance::finalizeUpdates() {
        auto rnInstancePtr = this->m_deps->rnInstance.lock();
        if (rnInstancePtr != nullptr) {
            auto turboModule = rnInstancePtr->getTurboModule("RNCSmartRefreshContext");
            auto arkTsTurboModule = std::dynamic_pointer_cast<rnoh::ArkTSTurboModule>(turboModule);
            folly::dynamic result = arkTsTurboModule->callSync("cvp2px", {getLayoutMetrics().frame.size.width});
            folly::dynamic result1 = arkTsTurboModule->callSync("cvp2px", {60});
            m_stackNode.setLayoutRect({0, 0}, {result["values"].asDouble(), result1["values"].asDouble()}, 1.0);
        }
        m_stackNode.setAlignment(ARKUI_ALIGNMENT_BOTTOM);
    }

    facebook::react::SharedColor RNCMaterialHeaderComponentInstance::GetPrimaryColor() { return -1; }

    void RNCMaterialHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                             std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
        getParent().lock()->getComponentName();
    }

    void RNCMaterialHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    SmartStackNode &RNCMaterialHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }


    void RNCMaterialHeaderComponentInstance::onRefreshStatusChange(int32_t status) {
        switch (status) {
        case IS_FREE:
        {
            float x = static_cast<float>((mWindowWidth - 46) / 2.0);
            float y = -46.0;
            ArkUI_NumberValue positionArray[] = {{.f32 = x}, {.f32 = y}};
            ArkUI_AttributeItem positionValue[] = {positionArray, 2};
            NativeNodeApi::getInstance()->setAttribute(imageStack.getArkUINodeHandle(), NODE_POSITION, positionValue);
        }
        case IS_PULL_DOWN_1:
        case IS_PULL_DOWN_2: {
            isRefreshed = false;
            progressNode.setLoadingProgressNodeColor(0xff0099cc);
        } break;
        case IS_REFRESHING: {
            progressNode.setLoadingProgressNodeColor(0xffff4444);
        }

        break;
        case IS_REFRESHED: {
            isRefreshed = true;
            progressNode.setLoadingProgressNodeColor(0xffaa66cc);
            setScaleAnimate(1000);
        } break;
        }
    }
} // namespace rnoh