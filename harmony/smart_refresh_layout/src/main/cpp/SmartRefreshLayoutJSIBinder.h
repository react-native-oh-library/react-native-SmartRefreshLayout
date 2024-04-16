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
#ifndef SMART_SRC_MAIN_CPP_SMARTREFRESHCONTROLCOMPONENTJSIBINDER_H
#define SMART_SRC_MAIN_CPP_SMARTREFRESHCONTROLCOMPONENTJSIBINDER_H
#include "RNOH/BaseComponentJSIBinder.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
    class SmartRefreshLayoutJSIBinder : public ViewComponentJSIBinder {
    protected:
        facebook::jsi::Object createBubblingEventTypes(facebook::jsi::Runtime &rt) override {
            auto events = ViewComponentJSIBinder::createBubblingEventTypes(rt);
            return events;
        }

        facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
            auto nativeProps = ViewComponentJSIBinder::createNativeProps(rt);
            nativeProps.setProperty(rt, "overScrollBounce", "boolean");
            nativeProps.setProperty(rt, "headerHeight", "number");
            nativeProps.setProperty(rt, "primaryColor", "number");
            nativeProps.setProperty(rt, "enableRefresh", "boolean");
            nativeProps.setProperty(rt, "dragRate", "number");
            nativeProps.setProperty(rt, "maxDragRate", "number");
            nativeProps.setProperty(rt, "overScrollBounce", "boolean");
            nativeProps.setProperty(rt, "overScrollDrag", "boolean");
            nativeProps.setProperty(rt, "pureScroll", "boolean");
            nativeProps.setProperty(rt, "autoRefresh", "object");
            return nativeProps;
        }

        facebook::jsi::Object createDirectEventTypes(facebook::jsi::Runtime &rt) override {
            facebook::jsi::Object events(rt);
            events.setProperty(rt, "topRefresh", createDirectEvent(rt, "onRefresh"));
            events.setProperty(rt, "topHeaderMoving", createDirectEvent(rt, "onHeaderMoving"));
            events.setProperty(rt, "topHeaderReleasing", createDirectEvent(rt, "onHeaderReleasing"));
            events.setProperty(rt, "topHeaderPulling", createDirectEvent(rt, "onHeaderPulling"));
            events.setProperty(rt, "topPullDownToRefresh", createDirectEvent(rt, "onPullDownToRefresh"));
            events.setProperty(rt, "topReleaseToRefresh", createDirectEvent(rt, "onReleaseToRefresh"));
            events.setProperty(rt, "topHeaderReleased", createDirectEvent(rt, "onHeaderReleased"));
            return events;
        }
    };

} // namespace rnoh
#endif