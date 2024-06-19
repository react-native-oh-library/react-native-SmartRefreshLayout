//
// Created on 2024/3/28.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include <string>
typedef enum {
    IS_FREE = 0x01,
    IS_PULL_DOWN_1 = 0x02,
    IS_PULL_DOWN_2 = 0x03,
    IS_REFRESHING = 0x04,
    IS_REFRESHED = 0x05,
    IS_PULL_UP_1 = 0x06,
    IS_PULL_UP_2 = 0x07,
    IS_LOADING = 0x08,
} Smart_Status;
const std::string MOMENTS[] = {"中午", "凌晨", "早上", "下午", "晚上"};