//
// Created on 10/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_ANIMATION_H
#define HARMONY_ANIMATION_H
#include <string>
#include <react/renderer/graphics/Color.h>
#include <regex>

class SmartUtils {
public:
    static facebook::react::SharedColor parseColor(std::string backColor) {
        if (backColor != "" && backColor.find("rgb") != std::string::npos) {
            return parseRgbOrRgba(backColor);
        }
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

    static facebook::react::SharedColor parseRgbOrRgba(const std::string &colorStr) {
        std::regex colorRegex(R"(rgb(a)?\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*(?:,\s*([01]|0\.\d+|1\.0*)\s*)?\))");
        std::smatch matchResult;
        if (!std::regex_match(colorStr, matchResult, colorRegex)) {
            return -1;
        }
        float r = std::stoi(matchResult[2]) / 255.0;
        float g = std::stoi(matchResult[3]) / 255.0;
        float b = std::stoi(matchResult[4]) / 255.0;
        float a = 1.0f;
        if (matchResult[1].matched) {
            if (matchResult[5].matched) {
                a = std::stof(matchResult[5]);
            } else {
                return -1;
            }
        }
       return facebook::react::colorFromComponents({r, g, b, a});
    }

    // NOTE: ArkUI translation is in `px` units, while React Native uses `vp`
    static double vp2px(double pointScaleFactor, double value) { return pointScaleFactor * value; }
};
#endif // HARMONY_ANIMATION_H