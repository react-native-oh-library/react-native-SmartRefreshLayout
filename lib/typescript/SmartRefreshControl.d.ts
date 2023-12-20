import React from "react";
import type * as ReactNative from "react-native";
import RNCSmartRefreshLayout, { NativeProps as Props, OnHeaderEventData } from "./fabric/SmartRefreshControlNativeComponent";
import type { DirectEventHandler } from "react-native/Libraries/Types/CodegenTypes";
declare type SmartRefreshControlProps = Props & {
    HeaderComponent?: React.ReactNode;
    renderHeader?: () => React.ReactElement | React.ReactElement;
    onHeaderMoving?: DirectEventHandler<OnHeaderEventData>;
};
export declare class SmartRefreshControl extends React.Component<SmartRefreshControlProps> {
    private _panResponder;
    smartRefreshLayout: React.ElementRef<typeof RNCSmartRefreshLayout> | null;
    static constants: {
        TRANSLATE: any;
        SCALE: any;
        FIX_BEHIND: any;
        FIX_FRONT: any;
        MATCH_LAYOUT: any;
    };
    /**
     * 参数格式为{delayed:number,success:bool}
     * delayed:延迟刷新
     * success:是否刷新成功
     * @param params
     */
    finishRefresh: ({ delayed, success }?: {
        delayed?: number;
        success?: true;
    }) => void;
    findNode: () => number | null;
    componentWillMount(): void;
    shiftPercent: number;
    footerShiftPercent: number;
    /**
     * 渲染Header
     * @return {*}
     */
    renderHeader: () => string | number | true | Iterable<React.ReactNode> | React.JSX.Element;
    /**
     * 刷新时触发
     * @private
     */
    private _onSmartRefresh;
    /**
     * 下拉过程
     * @param event
     * @private
     */
    _onHeaderPulling: (event: ReactNative.NativeSyntheticEvent<OnHeaderEventData>) => void;
    /**
     * 释放过程
     * @param event
     * @private
     */
    _onHeaderReleasing: (event: ReactNative.NativeSyntheticEvent<OnHeaderEventData>) => void;
    /**
     * 底部位移过程
     * @param event
     * @private
     */
    _onFooterMoving: (event: ReactNative.NativeSyntheticEvent<OnHeaderEventData>) => void;
    render(): React.JSX.Element;
}
export default SmartRefreshControl;
