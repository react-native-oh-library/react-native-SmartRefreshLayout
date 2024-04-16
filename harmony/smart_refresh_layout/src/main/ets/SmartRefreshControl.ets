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
    Tag,
    ColorSegments,
    convertColorSegmentsToString,
    RNScrollViewManager,
} from '@rnoh/react-native-openharmony'
import { PullToRefresh } from './PullToRefresh'
import { PullToRefreshConfigurator } from './PullToRefreshConfigurator'
import Logger from './Logger'

const TAG: string = "[RNOH] SmartRefreshLayout"
export const SMART_REFRESH_CONTROL_TYPE = "SmartRefreshLayout"

interface AutoRefresh{
    refresh: boolean
    time: number
}

export interface SmartRefreshLayoutProps extends ViewBaseProps {
    overScrollBounce: boolean,
    enableRefresh: boolean,
    headerHeight: number,
    overScrollDrag: boolean,
    pureScroll: boolean,
    dragRate: number,
    maxDragRate: number,
    primaryColor: ColorSegments,
    autoRefresh: AutoRefresh
}

export type SmartRefreshControlDescriptor = Descriptor<"SmartRefreshLayout", SmartRefreshLayoutProps>

@Component
export struct SmartRefreshControl {
    ctx!: RNOHContext
    tag: number = 0
    @BuilderParam buildCustomComponent: (componentBuilderContext: ComponentBuilderContext) => void
    @State descriptor: SmartRefreshControlDescriptor = {} as SmartRefreshControlDescriptor
    private unregisterDescriptorChangesListener?: () => void = undefined
    private cleanupCommandCallback?: () => void = undefined
    private unlockScrollingCallback?: () => void = undefined
    private scroller: Scroller = new Scroller();
    private pullToRefreshConfigurator:PullToRefreshConfigurator = new PullToRefreshConfigurator();
    private finishRefresh:(value: string | PromiseLike<string>) => void = ()=>{}
    private displayedHeaderHeight:number = 0;
    private scrollViewTag:number = -1;
    @State data: Tag[] = this.descriptor.childrenTags
    @Builder
    private getCustomList() {
        Stack(){
            RNComponentFactory({ ctx: this.ctx, tag: this.data[0], buildCustomComponent: this.buildCustomComponent })
        }
        .width('100%')
        .height('100%')
        .clip(true)
    }
    @Builder
    private header() {
        if (this.data[1]) {
            Stack(){
                RNComponentFactory({ ctx: this.ctx, tag: this.data[1], buildCustomComponent: this.buildCustomComponent })
            }
            .onAreaChange((oldValue: Area, newValue: Area) => {
                 Logger.debug(TAG,"RNOH SmartRefreshControl:onAreaChange " + JSON.stringify(newValue.height))
                this.checkHeaderMove(parseInt(newValue.height.toString()))
            })
            .width('100%')
            .height('100%')
            .clip(true)
        }
    }

    aboutToAppear() {
        this.descriptor = this.ctx.descriptorRegistry.getDescriptor<SmartRefreshControlDescriptor>(this.tag)
        this.init()

         Logger.info(TAG," SmartRefreshControl: props = " + JSON.stringify(this.descriptor.props))
         Logger.info(TAG," SmartRefreshControl: data = " + JSON.stringify(this.data))
        this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
            (newDescriptor) => {
                this.descriptor = (newDescriptor as SmartRefreshControlDescriptor)
                this.init()
            }
        )
        this.cleanupCommandCallback = this.ctx.componentCommandReceiver.registerCommandCallback(
            this.tag,
            (command, args:ESObject[]) => {
                if (command === 'finishRefresh') {
                     Logger.info(TAG," SmartRefreshControl: registerCommandCallback args = " + JSON.stringify(args))
                    let delayed: number = args[0]
                    let success: boolean = Boolean(args[1])
                    if (!isNaN(delayed)) {
                        if (delayed >= 0) {
                            this.pullToRefreshConfigurator.setFinishDelay(delayed)
                        } else {
                            this.pullToRefreshConfigurator.setFinishDelay(0)
                        }
                    } else {
                        this.pullToRefreshConfigurator.setFinishDelay(500)
                    }
                    this.finishRefresh?.("finish")
                }
            });
    }

    init(){
        this.pullToRefreshConfigurator.setMaxTranslate(this.descriptor.props.headerHeight * 2)
            .setRefreshBackgroundColor(convertColorSegmentsToString(this.descriptor.props.primaryColor) as ResourceColor)
            .setHasLoadMore(false)
            .setSensitivity(0.5)
        let child = this.ctx.descriptorRegistry.getDescriptor(this.descriptor.childrenTags[0])
        this.data = this.descriptor.childrenTags
        if (child.type === 'ScrollView') {
            this.scrollViewTag = child.tag
        }
         Logger.info(TAG," SmartRefreshControl: childrenTags = " + JSON.stringify(this.data))
    }

    aboutToDisappear() {
        this.unregisterDescriptorChangesListener?.()
        this.cleanupCommandCallback?.();
    }

    onRefresh(){
         Logger.info(TAG," SmartRefreshControl: onRefresh");
        this.ctx.rnInstance.emitComponentEvent(
            this.descriptor.tag,
            "onRefresh",
            {  }
        )
    }

    onHeaderPulling(displayedHeaderHeight:number){
        let percent = displayedHeaderHeight / this.descriptor.props.headerHeight
        this.ctx.rnInstance.emitComponentEvent(
            this.descriptor.tag,
            "onHeaderPulling",
            { percent:percent,offset:displayedHeaderHeight,headerHeight:this.descriptor.props.headerHeight }
        )
    }

    onHeaderReleasing(displayedHeaderHeight:number){
        let percent = displayedHeaderHeight / this.descriptor.props.headerHeight
        this.ctx.rnInstance.emitComponentEvent(
            this.descriptor.tag,
            "onHeaderReleasing",
            { percent:percent,offset:displayedHeaderHeight,headerHeight:this.descriptor.props.headerHeight }
        )
    }

    checkHeaderMove(displayedHeaderHeight:number){
        // 滚动时保持吸顶
        if (this.getScroller().currentOffset().yOffset !== 0 && displayedHeaderHeight > 0){
            this.getScroller().scrollEdge(Edge.Top)
        }
        if (this.unlockScrollingCallback === undefined && displayedHeaderHeight != 0){
            this.unlockScrollingCallback = this.getChildScrollViewComponentManager()?.lockScrolling()
        }
        if (this.unlockScrollingCallback !== undefined && displayedHeaderHeight == 0){
            this.unlockScrollingCallback()
            this.unlockScrollingCallback = undefined
        }
        // 下拉中
        if (this.displayedHeaderHeight < displayedHeaderHeight) {
            this.onHeaderPulling(displayedHeaderHeight)  // 下拉中
        } else if (this.displayedHeaderHeight > displayedHeaderHeight){
            this.onHeaderReleasing(displayedHeaderHeight) //回弹
        }
        this.displayedHeaderHeight = displayedHeaderHeight
    }

    // 因为子节点还没创建出来，需要延迟获取RNScrollViewManager
    getChildScrollViewComponentManager():RNScrollViewManager{
        let scrollViewComponentManager = this.ctx.componentManagerRegistry.getComponentManager(this.scrollViewTag) as RNScrollViewManager
        return scrollViewComponentManager
    }

    getScroller():Scroller{
        let scroller = this.getChildScrollViewComponentManager()?.getScroller() as Scroller
        if (scroller) {
            return scroller
        }else {
            console.warn("RNOH SmartRefreshControl getScroller fail ")
            return this.scroller
        }
    }

    build() {
        RNViewBase({ ctx: this.ctx, tag: this.tag }) {
            PullToRefresh({
                // 必传项，列表组件所绑定的数据
                data: $data,
                // 必传项，需绑定传入主体布局内的列表或宫格组件
                getScroller:()=>this.getScroller(),
                // 必传项，自定义主体布局，内部有列表或宫格组件
                customList: () => {
                    this.getCustomList()
                },
                // 可选项，下拉刷新回调
                onRefresh: () => {
                    return new Promise<string>((resolve, reject) => {
                        this.onRefresh()
                        this.finishRefresh = resolve
                    });
                },
                // 可选项，上拉加载更多回调
                onLoadMore: () => {
                    return new Promise<string>((resolve, reject) => {

                    });
                },
                customLoad: null,
                customRefresh: ()=>{this.header()},
                refreshConfigurator:this.pullToRefreshConfigurator
            })

        }
    }
}
