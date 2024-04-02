//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCMaterialHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "react/renderer/imagemanager/primitives.h"
#include "SmartRefreshState.h"

namespace rnoh {

    RNCMaterialHeaderComponentInstance::RNCMaterialHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        LOG(INFO) << "[tyBrave] <RNCMaterialHeaderComponentInstance {}";

        facebook::react::ImageSources imageSources;
        imageSources.push_back({.uri = "resource://BASE/media/icon_up.png"});
        imageNode.setSources(imageSources);
        imageNode.setSize({30, 20});
        imageNode.setResizeMode(facebook::react::ImageResizeMode::Contain);

        auto imageStack = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_STACK);

        ArkUI_NumberValue heightArray[] = {{.f32 = 45}};
        ArkUI_AttributeItem heightValue[] = {heightArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_HEIGHT, heightValue);
        ArkUI_NumberValue widthArray[] = {{.f32 = 45}};
        ArkUI_AttributeItem widthValue[] = {widthArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_WIDTH, widthValue);

        ArkUI_NumberValue shadowArray[] = {{.i32 = ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG}};
        ArkUI_AttributeItem shadowValue[] = {shadowArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_SHADOW, shadowValue);

        ArkUI_NumberValue borderStyArray[] = {1};
        ArkUI_AttributeItem borderStyValue[] = {borderStyArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_BORDER_WIDTH, borderStyValue);

        ArkUI_NumberValue radiusArray[] = {{.f32 = 45}};
        ArkUI_AttributeItem radiusValue[] = {radiusArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_BORDER_RADIUS, radiusValue);

        ArkUI_NumberValue borderColorArray[] = {
            {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}, {.u32 = 0xFFaaaaaa}};
        ArkUI_AttributeItem borderColorValue[] = {borderColorArray, 4};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_BORDER_COLOR, borderColorValue);

        ArkUI_NumberValue z_indexArray[] = {{.f32 = 1000}};
        ArkUI_AttributeItem z_indexValue[] = {z_indexArray, 1};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_Z_INDEX, z_indexValue);

        //         ArkUI_NumberValue borderStyArray[] = {ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID};
        //         ArkUI_AttributeItem borderStyValue[] = {borderStyArray, 1};
        //         NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_BORDER_STYLE, borderStyValue);

        //         uint32_t colorValue =0xFFFFFF00; // facebook::react::isColorMeaningful(color) ? *color :
        //         *facebook::react::clearColor(); ArkUI_NumberValue preparedColorValue[] = {{.u32 = colorValue}};
        //         ArkUI_AttributeItem colorItem = {preparedColorValue, sizeof(preparedColorValue) /
        //         sizeof(ArkUI_NumberValue)}; NativeNodeApi::getInstance()->setAttribute(imageStack,
        //         NODE_BACKGROUND_COLOR, &colorItem);


        NativeNodeApi::getInstance()->insertChildAt(imageStack, imageNode.getArkUINodeHandle(), 0);

        ArkUI_NumberValue positionArray[] = {{.f32 = 80}, {.f32 = 90}};
        ArkUI_AttributeItem positionValue[] = {positionArray, 2};
        NativeNodeApi::getInstance()->setAttribute(imageStack, NODE_POSITION, positionValue);

        NativeNodeApi::getInstance()->insertChildAt(m_stackNode.getArkUINodeHandle(), imageStack, 0);
    }
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

    StackNode &RNCMaterialHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void RNCMaterialHeaderComponentInstance::finalizeUpdates() {
        m_stackNode.setAlignment(ARKUI_ALIGNMENT_CENTER);
        m_stackNode.setBackgroundColor(0XFFFFFF00);
        if (getParent().lock()) {
            LOG(INFO) << "[tyBrave] <RNCMaterialHeaderComponentInstance finalizeUpdates  "
                      << getParent().lock()->getComponentName();
        }
    
    }

    void RNCMaterialHeaderComponentInstance::setImageRotate(float angle) {
        ArkUI_NumberValue opacityValue[] = {{.f32 = 0}, {.f32 = 0}, {.f32 = 1}, {.f32 = angle}, {.f32 = 0}};
        ArkUI_AttributeItem opacityItem = {opacityValue, sizeof(opacityValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_ROTATE, &opacityItem);
    }

    void RNCMaterialHeaderComponentInstance::onRefreshStatusChange(int32_t status) {
        switch (status) {
        case IS_FREE:
        case IS_PULL_DOWN_1: {

        } break;
        case IS_REFRESHING: {
        }

        break;
        case IS_PULL_DOWN_2: {
        } break;
        case IS_REFRESHED: {

        } break;
        }
    }
} // namespace rnoh