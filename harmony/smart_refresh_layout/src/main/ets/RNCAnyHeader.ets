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
import {
    Descriptor,
    ComponentBuilderContext,
    RNComponentFactory,
    RNOHContext,
    RNViewBase,
    ViewBaseProps,
    Tag
} from 'rnoh'
import Logger from './Logger'

const TAG: string = "[RNOH] RNCAnyHeader"
export const ANY_HEADER_TYPE = "RNCAnyHeader"

export interface AnyHeaderProps extends ViewBaseProps {
    primaryColor:String
}

export type AnyHeaderDescriptor = Descriptor<"RNCAnyHeader", AnyHeaderProps>

@Component
export struct RNCAnyHeader {
    ctx!: RNOHContext
    tag: number = 0
    @BuilderParam buildCustomComponent: (componentBuilderContext: ComponentBuilderContext) => void
    @State descriptor: AnyHeaderDescriptor = {} as AnyHeaderDescriptor
    private unregisterDescriptorChangesListener?: () => void = undefined

    aboutToAppear() {
        this.descriptor = this.ctx.descriptorRegistry.getDescriptor<AnyHeaderDescriptor>(this.tag)
         Logger.info(TAG," AnyHeader: props = " + JSON.stringify(this.descriptor.props))
        this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
            (newDescriptor) => {
                this.descriptor = (newDescriptor as AnyHeaderDescriptor)
            }
        )
    }

    aboutToDisappear() {
        this.unregisterDescriptorChangesListener?.()
    }

    build() {
        Stack(){
            ForEach(this.descriptor.childrenTags, (tag:Tag) => {
                RNComponentFactory({ ctx: this.ctx, tag: tag, buildCustomComponent: this.buildCustomComponent })
            }, (tag:Tag) => tag.toString())
        }.width('100%').height('100%').clip(true)
    }
}
