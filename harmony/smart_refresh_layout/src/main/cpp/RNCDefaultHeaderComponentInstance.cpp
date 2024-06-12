//
// Created on 2024/3/23.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCDefaultHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "react/renderer/imagemanager/primitives.h"
#include "SmartRefreshState.h"

namespace rnoh {

    RNCDefaultHeaderComponentInstance::RNCDefaultHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        textNode.setTextContent("下拉刷新");
        textNode.setFontSize(15);
        textNode.setFontColor(0xffaaaaaa);

        facebook::react::ImageSources imageSources;
        imageSources.push_back({.uri = "resource://BASE/media/icon_up.png"});

        imageNode.setSources(imageSources);
        imageNode.setSize({30, 15});
        imageNode.setResizeMode(facebook::react::ImageResizeMode::Contain);

        progressNode.setLoadingProgressNodeColor(0x53658461);
        progressNode.setLoadingProgressNodeAnimating(true);
        progressNode.setSize({50, 50});


        mColumnHandle = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_ROW);

        ArkUI_NumberValue heightNumberValue[] = {50};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(mColumnHandle, NODE_HEIGHT, &heightItem);

        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, imageNode.getArkUINodeHandle(), 0);
        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, textNode.getArkUINodeHandle(), 1);

        NativeNodeApi::getInstance()->insertChildAt(m_stackNode.getArkUINodeHandle(), mColumnHandle, 0);
        NativeNodeApi::getInstance()->insertChildAt(m_stackNode.getArkUINodeHandle(), progressNode.getArkUINodeHandle(),
                                                    1);
    }
    void RNCDefaultHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                            std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCDefaultHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    SmartStackNode &RNCDefaultHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void RNCDefaultHeaderComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        if (props != nullptr) {
            facebook::react::SharedColor headerColor = props->primaryColor;
            if (props->accentColor) {
                textNode.setFontColor(props->accentColor);
                imageNode.setTintColor(props->accentColor);
            }
        }
    }

    void RNCDefaultHeaderComponentInstance::finalizeUpdates() {
        ArkUI_NumberValue heightNumberValue[] = {60};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(m_stackNode.getArkUINodeHandle(), NODE_HEIGHT, &heightItem);
        m_stackNode.setAlignment(ARKUI_ALIGNMENT_BOTTOM);
    }

    void RNCDefaultHeaderComponentInstance::setImageRotate(float angle) {
        ArkUI_NumberValue opacityValue[] = {{.f32 = 0}, {.f32 = 0}, {.f32 = 1}, {.f32 = angle}, {.f32 = 0}};
        ArkUI_AttributeItem opacityItem = {opacityValue, sizeof(opacityValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_ROTATE, &opacityItem);
    }

    void RNCDefaultHeaderComponentInstance::onRefreshStatusChange(int32_t status) {

        ArkUI_NumberValue imageNodeVisiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_VISIBLE}};
        ArkUI_AttributeItem imageNodeVisiblyAbleItem = {imageNodeVisiblyAbleValue, 1};
        NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                   &imageNodeVisiblyAbleItem);
        switch (status) {
        case IS_FREE:
        case IS_PULL_DOWN_1: {
            textNode.setTextContent("下拉刷新");
            setImageRotate(180.0);
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(progressNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        case IS_REFRESHING: {
            textNode.setTextContent("");
            ArkUI_NumberValue imageNodeVisiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem imageNodeVisiblyAbleItem = {imageNodeVisiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &imageNodeVisiblyAbleItem);

            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_VISIBLE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(progressNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        }

        break;
        case IS_PULL_DOWN_2: {
            textNode.setTextContent("释放刷新");
            setImageRotate(0.0);
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(progressNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        case IS_REFRESHED: {
            textNode.setTextContent("刷新完毕");
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(progressNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        }
    }
} // namespace rnoh