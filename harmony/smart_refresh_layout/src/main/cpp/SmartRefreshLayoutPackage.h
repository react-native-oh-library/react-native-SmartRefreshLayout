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

#ifndef SMART_SRC_MAIN_CPP_SMARTREFRESHLAYOUTPACKAGE_H
#define SMART_SRC_MAIN_CPP_SMARTREFRESHLAYOUTPACKAGE_H

#include "RNOH/Package.h"
#include "ComponentDescriptors.h"
#include "SmartRefreshLayoutJSIBinder.h"
#include "SmartRefreshLayoutNapiBinder.h"
#include "RNCAnyHeaderJSIBinder.h"
#include "RNCAnyHeaderNapiBinder.h"
#include "RNCDefaultHeaderJSIBinder.h"
#include "RNCDefaultHeaderNapiBinder.h"
#include "SmartRefreshLayoutEmitRequestHandler.h"
#include "RNCAnyHeaderComponentInstance.h"
#include "SmartRefreshLayoutComponentInstance.h"

namespace rnoh {

    class SmartRefreshLayoutPackageComponentInstanceFactoryDelegate : public ComponentInstanceFactoryDelegate {
    public:
        using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;

        ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
            if (ctx.componentName == "RNCAnyHeader") {
                return std::make_shared<RNCAnyHeaderComponentInstance>(std::move(ctx));
            } else if (ctx.componentName == "SmartRefreshLayout") {
                return std::make_shared<SmartRefreshLayoutComponentInstance>(std::move(ctx));
            }
            return nullptr;
        }
    };

    class SmartRefreshLayoutPackage : public Package {
    public:
        SmartRefreshLayoutPackage(Package::Context ctx) : Package(ctx) {}

        ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override {
            return std::make_shared<SmartRefreshLayoutPackageComponentInstanceFactoryDelegate>(m_ctx);
        }

        std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override {
            return {
                facebook::react::concreteComponentDescriptorProvider<
                    facebook::react::SmartRefreshLayoutComponentDescriptor>(),
                facebook::react::concreteComponentDescriptorProvider<
                    facebook::react::RNCAnyHeaderComponentDescriptor>(),
                facebook::react::concreteComponentDescriptorProvider<
                    facebook::react::RNCDefaultHeaderComponentDescriptor>(),
                //              facebook::react::concreteComponentDescriptorProvider<
                //                  facebook::react::RNCMaterialHeaderComponentDescriptor>(),
                //              facebook::react::concreteComponentDescriptorProvider<
                //                  facebook::react::RNCStoreHouseHeaderComponentDescriptor>(),
                //              facebook::react::concreteComponentDescriptorProvider<
                //                  facebook::react::RNCClassicsHeaderComponentDescriptor>(),
            };
        }

        ComponentJSIBinderByString createComponentJSIBinderByName() override {
            return {
                {"SmartRefreshLayout", std::make_shared<SmartRefreshLayoutJSIBinder>()},
                {"RNCAnyHeader", std::make_shared<RNCAnyHeaderJSIBinder>()},
                {"RNCDefaultHeader", std::make_shared<RNCDefaultHeaderJSIBinder>()},
            };
        }

        ComponentNapiBinderByString createComponentNapiBinderByName() override {
            return {
                {"SmartRefreshLayout", std::make_shared<SmartRefreshLayoutNapiBinder>()},
                {"RNCAnyHeader", std::make_shared<RNCAnyHeaderNapiBinder>()},
                {"RNCDefaultHeader", std::make_shared<RNCDefaultHeaderNapiBinder>()},
            };
        }

        EventEmitRequestHandlers createEventEmitRequestHandlers() override {
            return {std::make_shared<SmartRefreshLayoutEmitRequestHandler>()};
        }
    };
} // namespace rnoh
#endif