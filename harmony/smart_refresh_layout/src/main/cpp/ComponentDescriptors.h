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

#ifndef SMART_SRC_MAIN_CPP_COMPONENTDESCRIPTORS_H
#define SMART_SRC_MAIN_CPP_COMPONENTDESCRIPTORS_H

#include "ShadowNodes.h"
#include <react/renderer/core/ConcreteComponentDescriptor.h>

namespace facebook {
namespace react {

using RNCAnyHeaderComponentDescriptor = ConcreteComponentDescriptor<RNCAnyHeaderShadowNode>;
using RNCClassicsHeaderComponentDescriptor = ConcreteComponentDescriptor<RNCClassicsHeaderShadowNode>;
using RNCDefaultHeaderComponentDescriptor = ConcreteComponentDescriptor<RNCDefaultHeaderShadowNode>;
using RNCMaterialHeaderComponentDescriptor = ConcreteComponentDescriptor<RNCMaterialHeaderShadowNode>;
using SmartRefreshLayoutComponentDescriptor = ConcreteComponentDescriptor<SmartRefreshLayoutShadowNode>;
using RNCStoreHouseHeaderComponentDescriptor = ConcreteComponentDescriptor<RNCStoreHouseHeaderShadowNode>;

} // namespace react
} // namespace facebook

#endif