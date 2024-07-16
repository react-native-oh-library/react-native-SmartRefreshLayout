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
    uint32_t enableLoadingProgressNodeAnimation = enable ? 1 : 0;
    std::array<ArkUI_NumberValue, 1> enableLoadingProgressNodeAnimationValue = {
        {{.u32 = enableLoadingProgressNodeAnimation}}};

    ArkUI_AttributeItem enableLoadingProgressNodeAnimationItem = {enableLoadingProgressNodeAnimationValue.data(),
                                                                  enableLoadingProgressNodeAnimationValue.size()};

    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING,
                                                          &enableLoadingProgressNodeAnimationItem));
}

} // namespace rnoh
