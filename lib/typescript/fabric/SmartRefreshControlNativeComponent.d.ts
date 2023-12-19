/// <reference types="react-native/types/modules/codegen" />
import React from "react";
import { ViewProps, HostComponent } from "react-native";
import type { DirectEventHandler, WithDefault, Float } from "react-native/Libraries/Types/CodegenTypes";
import { ProcessedColorValue } from "react-native/Libraries/StyleSheet/processColor";
export declare type OnHeaderEventData = Readonly<{
    percent: Float;
    offset: Float;
    headerHeight: Float;
}>;
export declare type VoidEventData = Readonly<{}>;
declare type AutoRefresh = Readonly<{
    refresh?: boolean;
    time?: Float;
}>;
export interface NativeProps extends ViewProps {
    overScrollBounce?: WithDefault<boolean, true>;
    onRefresh?: DirectEventHandler<VoidEventData>;
    onHeaderPulling?: DirectEventHandler<OnHeaderEventData>;
    onHeaderReleasing?: DirectEventHandler<OnHeaderEventData>;
    onPullDownToRefresh?: DirectEventHandler<VoidEventData>;
    onReleaseToRefresh?: DirectEventHandler<VoidEventData>;
    onHeaderReleased?: DirectEventHandler<VoidEventData>;
    enableRefresh?: WithDefault<boolean, true>;
    headerHeight?: Float;
    overScrollDrag?: WithDefault<boolean, true>;
    pureScroll?: WithDefault<boolean, false>;
    dragRate?: WithDefault<Float, 0.5>;
    maxDragRate?: WithDefault<Float, 2.0>;
    primaryColor?: ProcessedColorValue;
    autoRefresh?: AutoRefresh;
}
declare const _default: import("react-native/Libraries/Utilities/codegenNativeComponent").NativeComponentType<NativeProps>;
export default _default;
declare type SmartRefreshControlType = HostComponent<NativeProps>;
export interface NativeCommands {
    finishRefresh: (viewRef: React.ElementRef<SmartRefreshControlType>, delayed: Float, success: boolean) => void;
}
export declare const Commands: NativeCommands;
