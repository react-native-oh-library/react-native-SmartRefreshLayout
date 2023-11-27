import React from 'react';
import {
    ViewProps,ColorValue,HostComponent
} from 'react-native';
import codegenNativeCommands from 'react-native/Libraries/Utilities/codegenNativeCommands';
import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent";
import type {
    DirectEventHandler,WithDefault,Float
} from 'react-native/Libraries/Types/CodegenTypes';
import {ProcessedColorValue} from "react-native/Libraries/StyleSheet/processColor";

export type OnHeaderEventData = Readonly<{
    percent: Float;
    offset: Float;
    headerHeight: Float;
}>;

export type VoidEventData = Readonly<{

}>;

type AutoRefresh = Readonly<{
    refresh?: boolean;
    time?: Float;
}>
// todo
// | WithDefault<boolean, false>;

export interface NativeProps extends ViewProps{
    // nativeProps
    overScrollBounce?:WithDefault<boolean,true>,
    onRefresh?: DirectEventHandler<VoidEventData>, // todo 名字待检测
    // onLoadMore: PropTypes.func, 未使用
    onHeaderPulling?:DirectEventHandler<OnHeaderEventData>,
    onHeaderReleasing?:DirectEventHandler<OnHeaderEventData>,
    onPullDownToRefresh?:DirectEventHandler<VoidEventData>,
    onReleaseToRefresh?:DirectEventHandler<VoidEventData>,
    onHeaderReleased?:DirectEventHandler<VoidEventData>,
    enableRefresh?: WithDefault<boolean, true>,//是否启用下拉刷新功能
    headerHeight?:Float,
    overScrollDrag?:WithDefault<boolean, true>,//是否使用越界拖动，类似IOS样式
    pureScroll?:WithDefault<boolean, false>,//是否使用纯滚动模式
    dragRate?:WithDefault<Float, 0.5>,// 显示下拉高度/手指真实下拉高度=阻尼效果
    maxDragRate?:WithDefault<Float, 2.0>,//最大显示下拉高度/Header标准高度
    primaryColor?:ProcessedColorValue, // todo 类型不确定
    autoRefresh?:AutoRefresh //是否启动自动刷新 todo 默认值
}

export default codegenNativeComponent<NativeProps>("SmartRefreshLayout");

    type SmartRefreshControlType = HostComponent<NativeProps>;

// todo 类型
export interface NativeCommands {
    finishRefresh: (
        viewRef: React.ElementRef<SmartRefreshControlType>,
        delayed : Float,
        success:boolean
    ) => void;
}

export const Commands: NativeCommands = codegenNativeCommands<NativeCommands>({
    supportedCommands: [
        'finishRefresh'
    ],
});

