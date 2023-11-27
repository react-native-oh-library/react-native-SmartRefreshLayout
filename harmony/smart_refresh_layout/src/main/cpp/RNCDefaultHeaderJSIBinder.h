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
#pragma once
#include "RNOH/UIManagerModule.h"
#include "RNOH/BaseComponentJSIBinder.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class RNCDefaultHeaderJSIBinder : public ViewComponentJSIBinder {
protected:
    facebook::jsi::Object createBubblingEventTypes(facebook::jsi::Runtime &rt) override {
        auto events = ViewComponentJSIBinder::createBubblingEventTypes(rt);
        return events;
    }

    facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
        auto nativeProps = ViewComponentJSIBinder::createNativeProps(rt);
        nativeProps.setProperty(rt, "primaryColor", "number");
        nativeProps.setProperty(rt, "accentColor", "string");
        return nativeProps;
    }
};

} // namespace rnoh