//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNOH/BaseComponentNapiBinder.h"
#include "Props.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentNapiBinder.h"

namespace rnoh {

    class RNCMaterialHeaderNapiBinder : public ViewComponentNapiBinder {
    public:
        napi_value createProps(napi_env env, facebook::react::ShadowView const shadowView) override {
            napi_value napiBaseProps = ViewComponentNapiBinder::createProps(env, shadowView);
            if (auto props =
                    std::dynamic_pointer_cast<const facebook::react::RNCMaterialHeaderProps>(shadowView.props)) {
                return ArkJS(env)
                    .getObjectBuilder(napiBaseProps)
                    .build();
            }
            return napiBaseProps;
        };
    };

} // namespace rnoh
