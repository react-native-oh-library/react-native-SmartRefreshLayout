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

#ifndef SMART_SRC_MAIN_CPP_EVENTEMITTERS_H
#define SMART_SRC_MAIN_CPP_EVENTEMITTERS_H

#include <react/renderer/components/view/ViewEventEmitter.h>
#include <jsi/jsi.h>

namespace facebook {
namespace react {

class JSI_EXPORT RNCAnyHeaderEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  

  
};
class JSI_EXPORT RNCClassicsHeaderEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  

  
};
class JSI_EXPORT RNCDefaultHeaderEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  

  
};
class JSI_EXPORT RNCMaterialHeaderEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  

  
};
class JSI_EXPORT SmartRefreshLayoutEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  struct OnRefresh {
      
    };

  struct OnHeaderPulling {
      Float percent;
    Float offset;
    Float headerHeight;
    };

  struct OnHeaderReleasing {
      Float percent;
    Float offset;
    Float headerHeight;
    };

  struct OnPullDownToRefresh {
      
    };

  struct OnReleaseToRefresh {
      
    };

  struct OnHeaderReleased {
      
    };

  void onRefresh(OnRefresh value) const;

  void onHeaderPulling(OnHeaderPulling value) const;

  void onHeaderReleasing(OnHeaderReleasing value) const;

  void onPullDownToRefresh(OnPullDownToRefresh value) const;

  void onReleaseToRefresh(OnReleaseToRefresh value) const;

  void onHeaderReleased(OnHeaderReleased value) const;
};
class JSI_EXPORT RNCStoreHouseHeaderEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  

  
};

} // namespace react
} // namespace facebook
#endif