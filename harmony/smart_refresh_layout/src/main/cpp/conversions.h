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

#ifndef SMART_SRC_MAIN_CPP_CONVERSIONS_H
#define SMART_SRC_MAIN_CPP_CONVERSIONS_H

#include <folly/dynamic.h>
#include <react/renderer/components/scrollview/primitives.h>
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>

namespace facebook {
namespace react {

inline void fromRawValue(
    const PropsParserContext &context,
    const RawValue &value,
    ScrollViewSnapToAlignment &result) {
  auto string = (std::string)value;
  if (string == "start") {
    result = ScrollViewSnapToAlignment::Start;
    return;
  }
  if (string == "center") {
    result = ScrollViewSnapToAlignment::Center;
    return;
  }
  if (string == "end") {
    result = ScrollViewSnapToAlignment::End;
    return;
  }
  abort();
}

inline void fromRawValue(
    const PropsParserContext &context,
    const RawValue &value,
    ScrollViewIndicatorStyle &result) {
  auto string = (std::string)value;
  if (string == "default") {
    result = ScrollViewIndicatorStyle::Default;
    return;
  }
  if (string == "black") {
    result = ScrollViewIndicatorStyle::Black;
    return;
  }
  if (string == "white") {
    result = ScrollViewIndicatorStyle::White;
    return;
  }
  abort();
}

inline void fromRawValue(
    const PropsParserContext &context,
    const RawValue &value,
    ScrollViewKeyboardDismissMode &result) {
  auto string = (std::string)value;
  if (string == "none") {
    result = ScrollViewKeyboardDismissMode::None;
    return;
  }
  if (string == "on-drag") {
    result = ScrollViewKeyboardDismissMode::OnDrag;
    return;
  }
  if (string == "interactive") {
    result = ScrollViewKeyboardDismissMode::Interactive;
    return;
  }
  abort();
}

inline void fromRawValue(
    const PropsParserContext &context,
    const RawValue &value,
    ContentInsetAdjustmentBehavior &result) {
  auto string = (std::string)value;
  if (string == "never") {
    result = ContentInsetAdjustmentBehavior::Never;
    return;
  }
  if (string == "automatic") {
    result = ContentInsetAdjustmentBehavior::Automatic;
    return;
  }
  if (string == "scrollableAxes") {
    result = ContentInsetAdjustmentBehavior::ScrollableAxes;
    return;
  }
  if (string == "always") {
    result = ContentInsetAdjustmentBehavior::Always;
    return;
  }
  abort();
}

inline void fromRawValue(
    const PropsParserContext &context,
    const RawValue &value,
    ScrollViewMaintainVisibleContentPosition &result) {
  auto map = (butter::map<std::string, RawValue>)value;

  auto minIndexForVisible = map.find("minIndexForVisible");
  if (minIndexForVisible != map.end()) {
    fromRawValue(
        context, minIndexForVisible->second, result.minIndexForVisible);
  }
  auto autoscrollToTopThreshold = map.find("autoscrollToTopThreshold");
  if (autoscrollToTopThreshold != map.end()) {
    fromRawValue(
        context,
        autoscrollToTopThreshold->second,
        result.autoscrollToTopThreshold);
  }
}

inline std::string toString(const ScrollViewSnapToAlignment &value) {
  switch (value) {
    case ScrollViewSnapToAlignment::Start:
      return "start";
    case ScrollViewSnapToAlignment::Center:
      return "center";
    case ScrollViewSnapToAlignment::End:
      return "end";
  }
}

#if RN_DEBUG_STRING_CONVERTIBLE

inline std::string toString(const ScrollViewIndicatorStyle &value) {
  switch (value) {
    case ScrollViewIndicatorStyle::Default:
      return "default";
    case ScrollViewIndicatorStyle::Black:
      return "black";
    case ScrollViewIndicatorStyle::White:
      return "white";
  }
}

inline std::string toString(const ScrollViewKeyboardDismissMode &value) {
  switch (value) {
    case ScrollViewKeyboardDismissMode::None:
      return "none";
    case ScrollViewKeyboardDismissMode::OnDrag:
      return "on-drag";
    case ScrollViewKeyboardDismissMode::Interactive:
      return "interactive";
  }
}

inline std::string toString(const ContentInsetAdjustmentBehavior &value) {
  switch (value) {
    case ContentInsetAdjustmentBehavior::Never:
      return "never";
    case ContentInsetAdjustmentBehavior::Automatic:
      return "automatic";
    case ContentInsetAdjustmentBehavior::ScrollableAxes:
      return "scrollableAxes";
    case ContentInsetAdjustmentBehavior::Always:
      return "always";
  }
}

inline std::string toString(
    const std::optional<ScrollViewMaintainVisibleContentPosition> &value) {
  if (!value) {
    return "null";
  }
  return "{minIndexForVisible: " + toString(value.value().minIndexForVisible) +
      ", autoscrollToTopThreshold: " +
      toString(value.value().autoscrollToTopThreshold) + "}";
}

#endif

} // namespace react
} // namespace facebook
#endif