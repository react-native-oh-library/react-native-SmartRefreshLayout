//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SmartStackNode.h"
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

SmartStackNode::SmartStackNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK)) {
}

void SmartStackNode::insertChild(ArkUINode &child, std::size_t index) {
    maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(),
                                                           static_cast<int32_t>(index)));
}

void SmartStackNode::removeChild(ArkUINode &child) {
    maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
}

SmartStackNode &SmartStackNode::setMargin(float left, float top, float right, float bottom) {
    ArkUI_NumberValue value[] = {{.f32 = top}, {.f32 = right}, {.f32 = bottom}, {.f32 = left}};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_MARGIN, &item));
    return *this;
}

SmartStackNode::~SmartStackNode() {}

SmartStackNode &SmartStackNode::setAlign(int32_t align) {
    ArkUI_NumberValue value[] = {{.i32 = align}};
    ArkUI_AttributeItem item = {.value = value, .size = 1};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_STACK_ALIGN_CONTENT, &item));
    return *this;
}
} // namespace rnoh