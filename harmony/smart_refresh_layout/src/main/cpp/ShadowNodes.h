/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SMART_SRC_MAIN_CPP_SHADOWNODES_H
#define SMART_SRC_MAIN_CPP_SHADOWNODES_H

#include "EventEmitters.h"
#include "Props.h"
#include "States.h"
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <jsi/jsi.h>

namespace facebook {
namespace react {

JSI_EXPORT extern const char RNCAnyHeaderComponentName[];

/*
 * `ShadowNode` for <RNCAnyHeader> component.
 */
using RNCAnyHeaderShadowNode = ConcreteViewShadowNode<
    RNCAnyHeaderComponentName,
    RNCAnyHeaderProps,
    RNCAnyHeaderEventEmitter,
    RNCAnyHeaderState>;

JSI_EXPORT extern const char RNCClassicsHeaderComponentName[];

/*
 * `ShadowNode` for <RNCClassicsHeader> component.
 */
using RNCClassicsHeaderShadowNode = ConcreteViewShadowNode<
    RNCClassicsHeaderComponentName,
    RNCClassicsHeaderProps,
    RNCClassicsHeaderEventEmitter,
    RNCClassicsHeaderState>;

JSI_EXPORT extern const char RNCDefaultHeaderComponentName[];

/*
 * `ShadowNode` for <RNCDefaultHeader> component.
 */
using RNCDefaultHeaderShadowNode = ConcreteViewShadowNode<
    RNCDefaultHeaderComponentName,
    RNCDefaultHeaderProps,
    RNCDefaultHeaderEventEmitter,
    RNCDefaultHeaderState>;

JSI_EXPORT extern const char RNCMaterialHeaderComponentName[];

/*
 * `ShadowNode` for <RNCMaterialHeader> component.
 */
using RNCMaterialHeaderShadowNode = ConcreteViewShadowNode<
    RNCMaterialHeaderComponentName,
    RNCMaterialHeaderProps,
    RNCMaterialHeaderEventEmitter,
    RNCMaterialHeaderState>;

JSI_EXPORT extern const char SmartRefreshLayoutComponentName[];

/*
 * `ShadowNode` for <SmartRefreshLayout> component.
 */
using SmartRefreshLayoutShadowNode = ConcreteViewShadowNode<
    SmartRefreshLayoutComponentName,
    SmartRefreshLayoutProps,
    SmartRefreshLayoutEventEmitter,
    SmartRefreshLayoutState>;

JSI_EXPORT extern const char RNCStoreHouseHeaderComponentName[];

/*
 * `ShadowNode` for <RNCStoreHouseHeader> component.
 */
using RNCStoreHouseHeaderShadowNode = ConcreteViewShadowNode<
    RNCStoreHouseHeaderComponentName,
    RNCStoreHouseHeaderProps,
    RNCStoreHouseHeaderEventEmitter,
    RNCStoreHouseHeaderState>;

} // namespace react
} // namespace facebook
#endif