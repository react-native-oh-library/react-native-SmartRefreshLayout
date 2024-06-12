//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "RNOH/arkui/ArkUINode.h"
#include <react/renderer/imagemanager/primitives.h>

namespace rnoh {
class SmartImageNode : public ArkUINode {
 protected:
  ArkUI_NodeHandle m_childArkUINodeHandle;
  std::string m_uri;

  public:
  SmartImageNode();
  ~SmartImageNode();
  SmartImageNode& setSources(facebook::react::ImageSources const& src);
  SmartImageNode &setResizeMode(facebook::react::ImageResizeMode const &mode);
  SmartImageNode &setTintColor(facebook::react::SharedColor const &sharedColor);
};
} // namespace rnoh
