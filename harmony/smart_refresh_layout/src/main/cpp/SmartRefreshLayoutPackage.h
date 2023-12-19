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
#include "SmartRefreshControlComponentJSIBinder.h"
#include "SmartRefreshControlComponentNapiBinder.h"
#include "RNCAnyHeaderJSIBinder.h"
#include "RNCAnyHeaderNapiBinder.h"
#include "RNCDefaultHeaderJSIBinder.h"
#include "RNCDefaultHeaderNapiBinder.h"
#include "SmartRefreshLayoutEmitRequestHandler.h"

namespace rnoh {

class SmartRefreshLayoutPackage : public Package {
  public:
      SmartRefreshLayoutPackage(Package::Context ctx) : Package(ctx) {}

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
    
    ComponentJSIBinderByString createComponentJSIBinderByName() override{
        return {
        {"SmartRefreshLayout",std::make_shared<SmartRefreshControlComponentJSIBinder>()},
        {"RNCAnyHeader",std::make_shared<RNCAnyHeaderJSIBinder>()},
        {"RNCDefaultHeader",std::make_shared<RNCDefaultHeaderJSIBinder>()},
        };
    }
    
    ComponentNapiBinderByString createComponentNapiBinderByName() override{
        return {
        {"SmartRefreshLayout", std::make_shared<SmartRefreshLayoutComponentNapiBinder>()},
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