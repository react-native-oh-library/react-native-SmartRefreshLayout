//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SmartProgressNode.h"
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

SmartProgressNode::SmartProgressNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_LOADING_PROGRESS)) {}

void SmartProgressNode::setLoadingProgressNodeColor(facebook::react::SharedColor const &color) {
    uint32_t colorValue = *color;
    ArkUI_NumberValue preparedColorValue[] = {{.u32 = colorValue}};
    ArkUI_AttributeItem colorItem = {preparedColorValue, sizeof(preparedColorValue) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_LOADING_PROGRESS_COLOR, &colorItem));
}

void SmartProgressNode::setLoadingProgressNodeAnimating(const bool &enable) {
    uint32_t typeValue = 1;
    if (!enable) {
        typeValue = 0;
    }
    ArkUI_NumberValue preparedTypeValue[] = {{.u32 = typeValue}};
    ArkUI_AttributeItem typeItem = {preparedTypeValue, sizeof(preparedTypeValue) / sizeof(ArkUI_NumberValue)};
    maybeThrow(
        NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING, &typeItem));
}

} // namespace rnoh
