//
// Created on 2024/3/28.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include <string>
enum { IS_FREE, IS_PULL_DOWN_1, IS_PULL_DOWN_2, IS_REFRESHING, IS_REFRESHED, IS_PULL_UP_1, IS_PULL_UP_2, IS_LOADING };
const std::string MOMENTS[]={"中午", "凌晨", "早上", "下午", "晚上"};