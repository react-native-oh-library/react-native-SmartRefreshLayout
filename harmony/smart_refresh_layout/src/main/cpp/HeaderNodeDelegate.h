//
// Created on 2024/4/1.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#pragma once

#include "boost/cstdint.hpp"
namespace rnoh {
    class HeaderNodeDelegate {
    public:
        virtual ~HeaderNodeDelegate() = default;
        virtual void onRefreshStatusChange(int32_t status){};
    };
}
