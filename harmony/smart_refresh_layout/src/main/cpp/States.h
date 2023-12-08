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
#ifndef SMART_SRC_MAIN_CPP_STATES_H
#define SMART_SRC_MAIN_CPP_STATES_H

#ifdef ANDROID
#include <folly/dynamic.h>
#include <react/renderer/mapbuffer/MapBuffer.h>
#include <react/renderer/mapbuffer/MapBufferBuilder.h>
#endif

namespace facebook {
namespace react {

class RNCAnyHeaderState {
public:
  RNCAnyHeaderState() = default;

#ifdef ANDROID
  RNCAnyHeaderState(RNCAnyHeaderState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

class RNCClassicsHeaderState {
public:
  RNCClassicsHeaderState() = default;

#ifdef ANDROID
  RNCClassicsHeaderState(RNCClassicsHeaderState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

class RNCDefaultHeaderState {
public:
  RNCDefaultHeaderState() = default;

#ifdef ANDROID
  RNCDefaultHeaderState(RNCDefaultHeaderState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

class RNCMaterialHeaderState {
public:
  RNCMaterialHeaderState() = default;

#ifdef ANDROID
  RNCMaterialHeaderState(RNCMaterialHeaderState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

class SmartRefreshLayoutState {
public:
  SmartRefreshLayoutState() = default;

#ifdef ANDROID
  SmartRefreshLayoutState(SmartRefreshLayoutState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

class RNCStoreHouseHeaderState {
public:
  RNCStoreHouseHeaderState() = default;

#ifdef ANDROID
  RNCStoreHouseHeaderState(RNCStoreHouseHeaderState const &previousState, folly::dynamic data){};
  folly::dynamic getDynamic() const {
    return {};
  };
  MapBuffer getMapBuffer() const {
    return MapBufferBuilder::EMPTY();
  };
#endif
};

} // namespace react
} // namespace facebook
#endif