//
// Created on 10/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_ANIMATION_H
#define HARMONY_ANIMATION_H
#include <string>
#include <react/renderer/graphics/Color.h>

class SmartUtils {
public:
    static facebook::react::SharedColor parseColor(std::string backColor) {
        if (backColor != "" && backColor.find("#") != std::string::npos) {
            backColor = backColor.substr(1);
        }
        if (backColor == "") {
            return -1;
        }
        int num = std::stoi(backColor, NULL, 16);
        float alpha = (num >> 24 & 0xff) / 255.0;
        float red = (num >> 16 & 0xFF) / 255.0;
        // 移位8个字节位，并执行&操作，可以得出green部件的数值
        float green = (num >> 8 & 0xFF) / 255.0;
        // 低位8个字节执行&操作，可以得出blue部件的数值
        float blue = (num & 0xFF) / 255.0;
        if (backColor.length() == 6) {
            alpha = 1;
        }
        return facebook::react::colorFromComponents({red, green, blue, alpha});
    }
};
#endif // HARMONY_ANIMATION_H