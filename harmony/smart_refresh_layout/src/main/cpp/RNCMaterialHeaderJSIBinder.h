//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNOH/UIManagerModule.h"
#include "RNOH/BaseComponentJSIBinder.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
    class RNCMaterialHeaderJSIBinder : public ViewComponentJSIBinder {
    protected:
        facebook::jsi::Object createBubblingEventTypes(facebook::jsi::Runtime &rt) override {
            auto events = ViewComponentJSIBinder::createBubblingEventTypes(rt);
            return events;
        }

        facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
            auto nativeProps = ViewComponentJSIBinder::createNativeProps(rt);
//             nativeProps.setProperty(rt, "primaryColor", "number");
//             nativeProps.setProperty(rt, "accentColor", "number");
            return nativeProps;
        }
    };

} // namespace rnoh
