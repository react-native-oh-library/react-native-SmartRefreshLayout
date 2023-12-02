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

const TAG: string = "[RNOH] RNCDefaultHeader"
export const DEFAULT_HEADER_TYPE = "RNCDefaultHeader"

export interface DefaultHeaderProps extends ViewBaseProps {
    primaryColor:String
}

export type DefaultHeaderDescriptor = Descriptor<"RNCDefaultHeader", DefaultHeaderProps>

@Component
export struct RNCDefaultHeader {
    ctx!: RNOHContext
    tag: number = 0
    @BuilderParam buildCustomComponent: (componentBuilderContext: ComponentBuilderContext) => void
    @State descriptor: DefaultHeaderDescriptor = {} as DefaultHeaderDescriptor
    private unregisterDescriptorChangesListener?: () => void = undefined

    aboutToAppear() {
        this.descriptor = this.ctx.descriptorRegistry.getDescriptor<DefaultHeaderDescriptor>(this.tag)
         Logger.info(TAG,"RNCDefaultHeader: props = " + JSON.stringify(this.descriptor.props))
        this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
            (newDescriptor) => {
                this.descriptor = (newDescriptor as DefaultHeaderDescriptor)
            }
        )
    }

    aboutToDisappear() {
        this.unregisterDescriptorChangesListener?.()
    }

    build() {
        RNViewBase({ ctx: this.ctx, tag: this.tag }) {

        }
    }
}
