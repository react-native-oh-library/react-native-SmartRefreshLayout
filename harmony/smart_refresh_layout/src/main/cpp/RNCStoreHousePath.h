//
// Created on 2024/7/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_RNCSTOREHOUSEPATH_H
#define HARMONY_RNCSTOREHOUSEPATH_H
#include <iostream>
#include <vector>
#include <glog/logging.h>

std::vector<float> point_a{24, 0, 1, 22, 1, 22, 1, 72, 24, 0, 47, 22, 47, 22, 47, 72, 1, 48, 47, 48};
std::vector<float> point_b{0,  0,  0, 72, 0,  0,  37, 0,  37, 0,  47, 11, 47, 11, 47, 26, 47, 26, 38, 36,
                           38, 36, 0, 36, 38, 36, 47, 46, 47, 46, 47, 61, 47, 61, 38, 71, 37, 72, 0,  72};
std::vector<float> point_c{47, 0, 0, 0, 0, 0, 0, 72, 0, 72, 47, 72};
std::vector<float> point_d{0, 0, 0, 72, 0, 0, 24, 0, 24, 0, 47, 22, 47, 22, 47, 48, 47, 48, 23, 72, 23, 72, 0, 72};
std::vector<float> point_e{0, 0, 0, 72, 0, 0, 47, 0, 0, 36, 37, 36, 0, 72, 47, 72};
std::vector<float> point_f{0, 0, 0, 72, 0, 0, 47, 0, 0, 36, 37, 36};
std::vector<float> point_g{47, 23, 47, 0, 47, 0, 0, 0, 0, 0, 0, 72, 0, 72, 47, 72, 47, 72, 47, 48, 47, 48, 24, 48};
std::vector<float> point_h{0, 0, 0, 72, 0, 36, 47, 36, 47, 0, 47, 72};
std::vector<float> point_i{0, 0, 47, 0, 24, 0, 24, 72, 0, 72, 47, 72};
std::vector<float> point_j{47, 0, 47, 72, 47, 72, 24, 72, 24, 72, 0, 48};
std::vector<float> point_k{0, 0, 0, 72, 47, 0, 3, 33, 3, 38, 47, 72};
std::vector<float> point_l{0, 0, 0, 72, 0, 72, 47, 72};
std::vector<float> point_m{0, 0, 0, 72, 0, 0, 24, 23, 24, 23, 47, 0, 47, 0, 47, 72};
std::vector<float> point_n{0, 0, 0, 72, 0, 0, 47, 72, 47, 72, 47, 0};
std::vector<float> point_o{0, 0, 0, 72, 0, 72, 47, 72, 47, 72, 47, 0, 47, 0, 0, 0};
std::vector<float> point_p{0, 0, 0, 72, 0, 0, 47, 0, 47, 0, 47, 36, 47, 36, 0, 36};
std::vector<float> point_q{0, 0, 0, 72, 0, 72, 23, 72, 23, 72, 47, 48, 47, 48, 47, 0, 47, 0, 0, 0, 24, 28, 47, 71};
std::vector<float> point_r{0, 0, 0, 72, 0, 0, 47, 0, 47, 0, 47, 36, 47, 36, 0, 36, 0, 37, 47, 72};
std::vector<float> point_s{47, 0, 0, 0, 0, 0, 0, 36, 0, 36, 47, 36, 47, 36, 47, 72, 47, 72, 0, 72};
std::vector<float> point_t{0, 0, 47, 0, 24, 0, 24, 72};
std::vector<float> point_u{0, 0, 0, 72, 0, 72, 47, 72, 47, 72, 47, 0};
std::vector<float> point_v{0, 0, 24, 72, 24, 72, 47, 0};
std::vector<float> point_w{0, 0, 0, 72, 0, 72, 24, 49, 24, 49, 47, 72, 47, 72, 47, 0};
std::vector<float> point_x{0, 0, 47, 72, 47, 0, 0, 72};
std::vector<float> point_y{0, 0, 24, 23, 47, 0, 24, 23, 24, 23, 24, 72};
std::vector<float> point_z{0, 0, 47, 0, 47, 0, 0, 72, 0, 72, 47, 72};
std::vector<float> point_0{0, 0, 0, 72, 0, 72, 47, 72, 47, 72, 47, 0, 47, 0, 0, 0};
std::vector<float> point_1{24, 0, 24, 72};
std::vector<float> point_2{0, 0, 47, 0, 47, 0, 47, 36, 47, 36, 0, 36, 0, 36, 0, 72, 0, 72, 47, 72};
std::vector<float> point_3{0, 0, 47, 0, 47, 0, 47, 36, 47, 36, 0, 36, 47, 36, 47, 72, 47, 72, 0, 72};
std::vector<float> point_4{0, 0, 0, 36, 0, 36, 47, 36, 47, 0, 47, 72};
std::vector<float> point_5{0, 0, 0, 36, 0, 36, 47, 36, 47, 36, 47, 72, 47, 72, 0, 72, 0, 0, 47, 0};
std::vector<float> point_6{0, 0, 0, 72, 0, 72, 47, 72, 47, 72, 47, 36, 47, 36, 0, 36};
std::vector<float> point_7{0, 0, 47, 0, 47, 0, 47, 72};
std::vector<float> point_8{0, 0, 0, 72, 0, 72, 47, 72, 47, 72, 47, 0, 47, 0, 0, 0, 0, 36, 47, 36};
std::vector<float> point_9{47, 0, 0, 0, 0, 0, 0, 36, 0, 36, 47, 36, 47, 0, 47, 72};
namespace rnoh {
class RNCStoreHousePath {
private:
    static std::vector<float> getArrayByChar(char c) {
        if (c >= 'a' && c <= 'z') {
            c = c - 32;
        }
        switch (c) {
        case 'A':
            return point_a;
        case 'B':
            return point_b;
        case 'C':
            return point_c;
        case 'D':
            return point_d;
        case 'E':
            return point_e;
        case 'F':
            return point_f;
        case 'G':
            return point_g;
        case 'H':
            return point_h;
        case 'I':
            return point_i;
        case 'J':
            return point_j;
        case 'K':
            return point_k;
        case 'L':
            return point_l;
        case 'M':
            return point_m;
    case 'N':
            return point_n;
        case 'O':
            return point_o;
        case 'P':
            return point_p;
        case 'Q':
            return point_q;
        case 'R':
            return point_r;
        case 'S':
            return point_s;
        case 'T':
            return point_t;
        case 'U':
            return point_u;
        case 'V':
            return point_v;
        case 'W':
            return point_w;
        case 'X':
            return point_x;
        case 'Y':
            return point_y;
        case 'Z':
            return point_z;
        case '0':
            return point_0;
        case '1':
            return point_1;
        case '2':
            return point_2;
        case '3':
            return point_3;
        case '4':
            return point_4;
        case '5':
            return point_5;
        case '6':
            return point_6;
        case '7':
            return point_7;
        case '8':
            return point_8;
        case '9':
            return point_9;
        default:
            throw "error:the character is not supported,only a-z and 0-9 are supported";
        }
    }
public:
    static std::vector<std::vector<float>> getPath(std::string str, float scale, int gapBetweenLetter) {
        std::vector<std::vector<float>> list;
        float offsetForWidth = 0;
        for (int i = 0; i < str.length(); i++) {
            int pos = str[i];
            std::vector<float> points = getArrayByChar(pos);
            int pointCount = points.size() / 4;
            for (int j = 0; j < pointCount; j++) {
                std::vector<float> line(4);
                for (int k = 0; k < 4; k++) {
                    float l = points[j * 4 + k];
                    // x
                    if (k % 2 == 0) {
                        line[k] = (l + offsetForWidth) * scale;
                    }
                    // y
                    else {
                        line[k] = l * scale;
                    }
                }
                list.push_back(line);
            }
            offsetForWidth += 57 + gapBetweenLetter;
        }
        return list;
    }
};
} // namespace rnoh

#endif // HARMONY_RNCSTOREHOUSEPATH_H