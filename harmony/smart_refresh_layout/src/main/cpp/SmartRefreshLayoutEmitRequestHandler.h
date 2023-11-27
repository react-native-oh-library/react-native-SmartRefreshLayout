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

#include <glog/logging.h>
#include "glog/logging.h"
#include "EventEmitters.h"
#include "RNOH/ArkJS.h"
#include "RNOH/EventEmitRequestHandler.h"

namespace rnoh {

class SmartRefreshLayoutEmitRequestHandler : public EventEmitRequestHandler {
public:
    void handleEvent(EventEmitRequestHandler::Context const &ctx) override {
        ArkJS arkJs(ctx.env);
        auto eventName = ctx.eventName;
        auto eventEmitter =
            ctx.shadowViewRegistry->getEventEmitter<facebook::react::SmartRefreshLayoutEventEmitter>(ctx.tag);
        if (eventEmitter == nullptr) {
            return;
        }

        if (eventName == "onRefresh") {
            eventEmitter->onRefresh({});
        }  else if (eventName == "onHeaderPulling") {
            float percent = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "percent"));
            float offset = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "offset"));
            float headerHeight = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "headerHeight"));
            facebook::react::SmartRefreshLayoutEventEmitter::OnHeaderPulling event{percent, offset, headerHeight};
            LOG(INFO) << "onHeaderPulling " << event.headerHeight << event.offset << event.percent;
            eventEmitter->onHeaderPulling(event);
        } else if (eventName == "onHeaderReleasing") {
            float percent = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "percent"));
            float offset = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "offset"));
            float headerHeight = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "headerHeight"));
            facebook::react::SmartRefreshLayoutEventEmitter::OnHeaderReleasing event{percent, offset, headerHeight};
            LOG(INFO) << "onHeaderReleasing " << event.headerHeight << event.offset << event.percent;
            eventEmitter->onHeaderReleasing(event);
        }
    }
};

} // namespace rnoh
