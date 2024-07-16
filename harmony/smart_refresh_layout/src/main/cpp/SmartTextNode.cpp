//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SmartTextNode.h"
#include "RNOH/arkui/NativeNodeApi.h"


namespace rnoh {

SmartTextNode::SmartTextNode() : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_TEXT)) {}

void SmartTextNode::insertChild(ArkUINode &child, std::size_t index) {
    maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(),
                                                           static_cast<int32_t>(index)));
}

void SmartTextNode::removeChild(ArkUINode &child) {
    maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
}

SmartTextNode &SmartTextNode::setTextContent(const std::string &text) {
    ArkUI_AttributeItem item = {.string = text.c_str()};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_TEXT_CONTENT, &item));
    return *this;
}

SmartTextNode &SmartTextNode::setFontColor(facebook::react::SharedColor const &color) {
    uint32_t colorValue = *color;
    ArkUI_NumberValue preparedColorValue[] = {{.u32 = colorValue}};
    ArkUI_AttributeItem colorItem = {preparedColorValue, sizeof(preparedColorValue) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_FONT_COLOR, &colorItem));
    return *this;
}

SmartTextNode &SmartTextNode::setFontSize(float fontSize) {
    ArkUI_NumberValue value[] = {{.f32 = fontSize}};
    ArkUI_AttributeItem item = {.value = value, .size = 1};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_FONT_SIZE, &item));
    return *this;
}
} // namespace rnoh
