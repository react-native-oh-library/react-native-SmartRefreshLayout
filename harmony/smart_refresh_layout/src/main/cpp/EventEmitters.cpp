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

#include "EventEmitters.h"

namespace facebook {
namespace react {

void SmartRefreshLayoutEventEmitter::onRefresh(OnRefresh event) const {
  dispatchEvent("refresh", [event=std::move(event)](jsi::Runtime &runtime) {
    auto payload = jsi::Object(runtime);
    
    return payload;
  });
}
void SmartRefreshLayoutEventEmitter::onHeaderPulling(OnHeaderPulling event) const {
  dispatchEvent("headerPulling", [event=std::move(event)](jsi::Runtime &runtime) {
    auto payload = jsi::Object(runtime);
    payload.setProperty(runtime, "percent", event.percent);
payload.setProperty(runtime, "offset", event.offset);
payload.setProperty(runtime, "headerHeight", event.headerHeight);
    return payload;
  });
}
void SmartRefreshLayoutEventEmitter::onHeaderReleasing(OnHeaderReleasing event) const {
  dispatchEvent("headerReleasing", [event=std::move(event)](jsi::Runtime &runtime) {
    auto payload = jsi::Object(runtime);
    payload.setProperty(runtime, "percent", event.percent);
payload.setProperty(runtime, "offset", event.offset);
payload.setProperty(runtime, "headerHeight", event.headerHeight);
    return payload;
  });
}
void SmartRefreshLayoutEventEmitter::onPullDownToRefresh(OnPullDownToRefresh event) const {
  dispatchEvent("pullDownToRefresh", [event=std::move(event)](jsi::Runtime &runtime) {
    auto payload = jsi::Object(runtime);
    
    return payload;
  });
}
void SmartRefreshLayoutEventEmitter::onReleaseToRefresh(OnReleaseToRefresh event) const {
  dispatchEvent("releaseToRefresh", [event=std::move(event)](jsi::Runtime &runtime) {
    auto payload = jsi::Object(runtime);
    
    return payload;
  });
}
void SmartRefreshLayoutEventEmitter::onHeaderReleased(OnHeaderReleased event) const {
  dispatchEvent("headerReleased", [event=std::move(event)](jsi::Runtime &runtime) {
    auto payload = jsi::Object(runtime);
    
    return payload;
  });
}


} // namespace react
} // namespace facebook
