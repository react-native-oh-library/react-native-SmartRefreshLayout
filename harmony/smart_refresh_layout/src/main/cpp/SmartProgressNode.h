//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {
class SmartProgressNode : public ArkUINode {
public:
    SmartProgressNode();

    void setLoadingProgressNodeColor(facebook::react::SharedColor const &color);

    void setLoadingProgressNodeAnimating(const bool &enable);
};
} // namespace rnoh
