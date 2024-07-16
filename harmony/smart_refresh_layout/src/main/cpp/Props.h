/**
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * you may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SMART_SRC_MAIN_CPP_PROPS_H
#define SMART_SRC_MAIN_CPP_PROPS_H

#include <jsi/jsi.h>
#include <react/renderer/components/view/ViewProps.h>
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>
#include <react/renderer/graphics/Color.h>
#include <string>

namespace facebook {
namespace react {

class JSI_EXPORT RNCAnyHeaderProps final : public ViewProps {
 public:
  RNCAnyHeaderProps() = default;
  RNCAnyHeaderProps(const PropsParserContext& context, const RNCAnyHeaderProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  std::string primaryColor{""};
};

class JSI_EXPORT RNCClassicsHeaderProps final : public ViewProps {
 public:
  RNCClassicsHeaderProps() = default;
  RNCClassicsHeaderProps(const PropsParserContext& context, const RNCClassicsHeaderProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  std::string primaryColor{};
  std::string accentColor{};
};

class JSI_EXPORT RNCDefaultHeaderProps final : public ViewProps {
 public:
  RNCDefaultHeaderProps() = default;
  RNCDefaultHeaderProps(const PropsParserContext& context, const RNCDefaultHeaderProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  std::string primaryColor{};
  std::string accentColor{};
};

class JSI_EXPORT RNCMaterialHeaderProps final : public ViewProps {
 public:
  RNCMaterialHeaderProps() = default;
  RNCMaterialHeaderProps(const PropsParserContext& context, const RNCMaterialHeaderProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  
};

struct SmartRefreshLayoutAutoRefreshStruct {
  bool refresh;
  Float time;
};

static inline void fromRawValue(const PropsParserContext& context, const RawValue &value, SmartRefreshLayoutAutoRefreshStruct &result) {
  auto map = (butter::map<std::string, RawValue>)value;

  auto tmp_refresh = map.find("refresh");
  if (tmp_refresh != map.end()) {
    fromRawValue(context, tmp_refresh->second, result.refresh);
  }
  auto tmp_time = map.find("time");
  if (tmp_time != map.end()) {
    fromRawValue(context, tmp_time->second, result.time);
  }
}

static inline std::string toString(const SmartRefreshLayoutAutoRefreshStruct &value) {
  return "[Object SmartRefreshLayoutAutoRefreshStruct]";
}
class JSI_EXPORT SmartRefreshLayoutProps final : public ViewProps {
 public:
  SmartRefreshLayoutProps() = default;
  SmartRefreshLayoutProps(const PropsParserContext& context, const SmartRefreshLayoutProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  bool overScrollBounce{true};
  bool enableRefresh{true};
  Float headerHeight{0.0};
  bool overScrollDrag{true};
  bool pureScroll{false};
  Float dragRate{0.5};
  Float maxDragRate{2.0};
  SharedColor primaryColor{};
  SmartRefreshLayoutAutoRefreshStruct autoRefresh{};
};

class JSI_EXPORT RNCStoreHouseHeaderProps final : public ViewProps {
 public:
  RNCStoreHouseHeaderProps() = default;
  RNCStoreHouseHeaderProps(const PropsParserContext& context, const RNCStoreHouseHeaderProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  std::string textColor{"#cccccc"};
  std::string text{"StoreHouse"};
  int fontSize{25};
  Float lineWidth{1};
  Float dropHeight{40};
};

} // namespace react
} // namespace facebook
#endif