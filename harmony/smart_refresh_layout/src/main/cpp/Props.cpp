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

#include "Props.h"
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>

namespace facebook {
namespace react {

RNCAnyHeaderProps::RNCAnyHeaderProps(
    const PropsParserContext &context,
    const RNCAnyHeaderProps &sourceProps,
    const RawProps &rawProps): ViewProps(context, sourceProps, rawProps),

    primaryColor(convertRawProp(context, rawProps, "primaryColor", sourceProps.primaryColor, {}))
      {}
RNCClassicsHeaderProps::RNCClassicsHeaderProps(
    const PropsParserContext &context,
    const RNCClassicsHeaderProps &sourceProps,
    const RawProps &rawProps): ViewProps(context, sourceProps, rawProps),

    primaryColor(convertRawProp(context, rawProps, "primaryColor", sourceProps.primaryColor, {})),
    accentColor(convertRawProp(context, rawProps, "accentColor", sourceProps.accentColor, {}))
      {}
RNCDefaultHeaderProps::RNCDefaultHeaderProps(
    const PropsParserContext &context,
    const RNCDefaultHeaderProps &sourceProps,
    const RawProps &rawProps): ViewProps(context, sourceProps, rawProps),

    primaryColor(convertRawProp(context, rawProps, "primaryColor", sourceProps.primaryColor, {})),
    accentColor(convertRawProp(context, rawProps, "accentColor", sourceProps.accentColor, {}))
      {}
RNCMaterialHeaderProps::RNCMaterialHeaderProps(
    const PropsParserContext &context,
    const RNCMaterialHeaderProps &sourceProps,
    const RawProps &rawProps): ViewProps(context, sourceProps, rawProps)

    
      {}
SmartRefreshLayoutProps::SmartRefreshLayoutProps(
    const PropsParserContext &context,
    const SmartRefreshLayoutProps &sourceProps,
    const RawProps &rawProps): ViewProps(context, sourceProps, rawProps),

    overScrollBounce(convertRawProp(context, rawProps, "overScrollBounce", sourceProps.overScrollBounce, {true})),
    enableRefresh(convertRawProp(context, rawProps, "enableRefresh", sourceProps.enableRefresh, {true})),
    headerHeight(convertRawProp(context, rawProps, "headerHeight", sourceProps.headerHeight, {0.0})),
    overScrollDrag(convertRawProp(context, rawProps, "overScrollDrag", sourceProps.overScrollDrag, {true})),
    pureScroll(convertRawProp(context, rawProps, "pureScroll", sourceProps.pureScroll, {false})),
    dragRate(convertRawProp(context, rawProps, "dragRate", sourceProps.dragRate, {0.5})),
    maxDragRate(convertRawProp(context, rawProps, "maxDragRate", sourceProps.maxDragRate, {2.0})),
    primaryColor(convertRawProp(context, rawProps, "primaryColor", sourceProps.primaryColor, {})),
    autoRefresh(convertRawProp(context, rawProps, "autoRefresh", sourceProps.autoRefresh, {}))
      {}
RNCStoreHouseHeaderProps::RNCStoreHouseHeaderProps(
    const PropsParserContext &context,
    const RNCStoreHouseHeaderProps &sourceProps,
    const RawProps &rawProps): ViewProps(context, sourceProps, rawProps),

    textColor(convertRawProp(context, rawProps, "textColor", sourceProps.textColor, {})),
    text(convertRawProp(context, rawProps, "text", sourceProps.text, {})),
    fontSize(convertRawProp(context, rawProps, "fontSize", sourceProps.fontSize, {25})),
    lineWidth(convertRawProp(context, rawProps, "lineWidth", sourceProps.lineWidth, {0.0})),
    dropHeight(convertRawProp(context, rawProps, "dropHeight", sourceProps.dropHeight, {0.0}))
      {}

} // namespace react
} // namespace facebook
