//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#pragma once
#include <glog/logging.h>
#include <memory>
#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {
class SmartStackNode : public ArkUINode {
public:
    SmartStackNode();
    ~SmartStackNode() override;
    void insertChild(ArkUINode &child, std::size_t index);
    void removeChild(ArkUINode &child);
    SmartStackNode &setMargin(float left, float top, float right, float bottom);
    SmartStackNode &setAlign(int32_t align);
};
} // namespace rnoh
