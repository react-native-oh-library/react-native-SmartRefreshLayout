//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SmartImageNode.h"

#include <string_view>
#include "RNOH/arkui/NativeNodeApi.h"

static constexpr ArkUI_NodeEventType IMAGE_NODE_EVENT_TYPES[] = {NODE_IMAGE_ON_COMPLETE, NODE_IMAGE_ON_ERROR};

namespace rnoh {

using namespace std::literals;
constexpr std::string_view ASSET_PREFIX = "asset://"sv;

SmartImageNode::SmartImageNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_IMAGE)),
      m_childArkUINodeHandle(nullptr) {}

SmartImageNode::~SmartImageNode() {}

SmartImageNode &SmartImageNode::setSources(facebook::react::ImageSources const &src) {
    ArkUI_AttributeItem item;
    m_uri = src[0].uri;
    std::string resourceStr = std::string("resource://RAWFILE/") + "assets/";
    if (m_uri.rfind(ASSET_PREFIX, 0) == 0) {
        resourceStr += m_uri.substr(ASSET_PREFIX.size());
        item = {.string = resourceStr.c_str()};
    } else {
        item = {.string = m_uri.c_str()};
    }
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_IMAGE_SRC, &item));
    return *this;
}

SmartImageNode &SmartImageNode::setResizeMode(facebook::react::ImageResizeMode const &mode) {
    int32_t val = ARKUI_OBJECT_FIT_COVER;
    if (mode == facebook::react::ImageResizeMode::Cover) {
        val = ARKUI_OBJECT_FIT_COVER;
    } else if (mode == facebook::react::ImageResizeMode::Contain) {
        val = ARKUI_OBJECT_FIT_CONTAIN;
    } else if (mode == facebook::react::ImageResizeMode::Stretch) {
        val = ARKUI_OBJECT_FIT_FILL;
    } else if (mode == facebook::react::ImageResizeMode::Center || mode == facebook::react::ImageResizeMode::Repeat) {
        val = ARKUI_OBJECT_FIT_NONE;
    }

    ArkUI_NumberValue value[] = {{.i32 = val}};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_IMAGE_OBJECT_FIT, &item));
    return *this;
}

SmartImageNode &SmartImageNode::setTintColor(facebook::react::SharedColor const &sharedColor) {
    if (!sharedColor) { // restore default value
        maybeThrow(NativeNodeApi::getInstance()->resetAttribute(m_nodeHandle, NODE_IMAGE_COLOR_FILTER));
        return *this;
    }

    facebook::react::ColorComponents com = colorComponentsFromColor(sharedColor);
    ArkUI_NumberValue value[] = {{.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = com.red},   {.f32 = 0},
                                 {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = com.green}, {.f32 = 0},
                                 {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = com.blue},  {.f32 = 0},
                                 {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 1},         {.f32 = 0}};

    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_IMAGE_COLOR_FILTER, &item));
    return *this;
}
} // namespace rnoh
