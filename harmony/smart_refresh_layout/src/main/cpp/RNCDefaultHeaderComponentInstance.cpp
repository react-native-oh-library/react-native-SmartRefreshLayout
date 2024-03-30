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
        LOG(INFO) << "[tyBrave] <RNCDefaultHeaderComponentInstance {}";
        textNode.setTextContent("下拉刷新");
        textNode.setFontSize(15);
        textNode.setFontColor(0xffaaaaaa);

        progressNode.setLoadingProgressNodeColor(0x53658461);
        progressNode.setLoadingProgressNodeAnimating(true);

        mColumnHandle = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_ROW);

        ArkUI_NumberValue heightNumberValue[] = {50};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(mColumnHandle, NODE_HEIGHT, &heightItem);

        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, textNode.getArkUINodeHandle(), 0);
        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, progressNode.getArkUINodeHandle(), 1);
        NativeNodeApi::getInstance()->insertChildAt(m_stackNode.getArkUINodeHandle(), mColumnHandle, 0);
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

    StackNode &RNCDefaultHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void RNCDefaultHeaderComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        if (props != nullptr) {
            primaryColor = props->primaryColor;
            LOG(INFO) << "[tyBrave] <RNCDefaultHeaderComponentInstance onPropsChanged{}";
        }
    }

    void RNCDefaultHeaderComponentInstance::finalizeUpdates() {
        ArkUI_NumberValue heightNumberValue[] = {60};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(m_stackNode.getArkUINodeHandle(), NODE_HEIGHT, &heightItem);
        m_stackNode.setAlignment(ARKUI_ALIGNMENT_BOTTOM);
    }
    void RNCDefaultHeaderComponentInstance::onRefreshStatusChange(int32_t status) {
        switch (status) {
        case IS_FREE:
        case IS_PULL_DOWN_1: {
            textNode.setTextContent("下拉刷新");
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(progressNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        case IS_REFRESHING: {
            textNode.setTextContent("");
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_VISIBLE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(progressNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        }

        break;
        case IS_PULL_DOWN_2: {
            textNode.setTextContent("释放刷新");
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