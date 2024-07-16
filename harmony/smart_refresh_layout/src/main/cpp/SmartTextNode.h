//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {
class SmartTextNode : public ArkUINode {
 private:
  enum {
    FLAG_PADDING = 0,
    FLAG_MINFONTSIZE,
    FLAG_MAXFONTSIZE,
    FLAG_COPYOPTION,
    FLAG_ENABLE,
    FLAG_MAX
  };
  bool m_initFlag[FLAG_MAX] = {0};

  float m_minFontSize = 0.0;
  float m_maxFontSize = 0.0;
  int32_t m_testCopyOption = 0;
  bool m_enableFlag = false;
  float m_top = 0.0;
  float m_right = 0.0;
  float m_bottom = 0.0;
  float m_left = 0.0;

 public:
  SmartTextNode();

  void insertChild(ArkUINode& child, std::size_t index);
  void removeChild(ArkUINode& child);

  SmartTextNode& setTextContent(const std::string& text);
  SmartTextNode& setFontColor(facebook::react::SharedColor const& color);
  SmartTextNode& setFontSize(float fontSize);
};
} // namespace rnoh
