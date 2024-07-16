//
// Created on 2024/4/1.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#pragma once

#include "RNOH/arkui/ArkUINode.h"
#include "boost/cstdint.hpp"
#include <arkui/native_type.h>
#include <bits/alltypes.h>
namespace rnoh {
    class HeaderNodeDelegate {
    public:
        virtual ~HeaderNodeDelegate() = default;
        virtual void onRefreshStatusChange(int32_t status){};
        virtual void addHeader(int32_t screenWidth, int32_t index, ArkUINode *arkUI_Node){};
        virtual void onHeaderMove(float dur){};
        virtual facebook::react::SharedColor GetPrimaryColor(){};
    };
} // namespace rnoh
