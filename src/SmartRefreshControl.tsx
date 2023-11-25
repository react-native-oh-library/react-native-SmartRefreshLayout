import React, {Component} from 'react';
import {
    StyleSheet,
    View,
    Image,
    Text,
    requireNativeComponent,
    findNodeHandle,
    UIManager,
    NativeModules,
    Platform,
    PanResponder,
    processColor
} from 'react-native';
import type * as ReactNative from 'react-native';
import RNCSmartRefreshLayout,{NativeProps as Props,Commands as SmartRefreshControlCommands,OnHeaderEventData,VoidEventData} from "./fabric/SmartRefreshControlNativeComponent";
import type {
    DirectEventHandler
} from 'react-native/Libraries/Types/CodegenTypes';
// import {processColor, ProcessedColorValue} from "react-native/Libraries/StyleSheet/processColor";
import {PanResponderInstance} from "react-native/Libraries/Interaction/PanResponder";
import {ColorValue} from "react-native/Libraries/StyleSheet/StyleSheet";
import DefaultHeader from './fabric/DefaultHeaderNativeComponent'
import AnyHeader from './AnyHeader'

const SPModule =Platform.OS === 'android' ? NativeModules.SpinnerStyleModule : {};

type SmartRefreshControlProps = Props & {
    HeaderComponent?:React.ReactNode;
    renderHeader?:()=>React.ReactElement | React.ReactElement;
    onHeaderMoving?:DirectEventHandler<OnHeaderEventData>,
}

export class SmartRefreshControl extends React.Component<SmartRefreshControlProps> {
    private _panResponder:PanResponderInstance |null = null ;
    smartRefreshLayout: React.ElementRef<typeof RNCSmartRefreshLayout> | null = null;

    static constants = {
        "TRANSLATE":SPModule.translate,
        "SCALE":SPModule.scale,
        "FIX_BEHIND":SPModule.fixBehind,
        "FIX_FRONT":SPModule.fixFront,
        "MATCH_LAYOUT":SPModule.matchLayout,
    }


    /**
     * 参数格式为{delayed:number,success:bool}
     * delayed:延迟刷新
     * success:是否刷新成功
     * @param params
     */
    finishRefresh=({delayed=-1,success=true}={delayed:-1,success:true})=>{
        // this.dispatchCommand('finishRefresh',[delayed,success])
        if (this.smartRefreshLayout){
            SmartRefreshControlCommands.finishRefresh(this.smartRefreshLayout,delayed,success)
        }
    }
    // dispatchCommand=(commandName:string, params:Array<any>)=>{
    //     UIManager.dispatchViewManagerCommand(this.findNode(),
    //         (UIManager.getViewManagerConfig ? UIManager.getViewManagerConfig("SmartRefreshLayout"): UIManager.SmartRefreshLayout).Commands[commandName],
    //         params);
    // }
    findNode=()=>{
        return findNodeHandle(this.smartRefreshLayout);
    }
    componentWillMount() {
        this._panResponder = PanResponder.create({
            onMoveShouldSetPanResponderCapture: (evt, gestureState) => {
                if(this.shiftPercent >= 0.039 || this.footerShiftPercent >= 0.068){//满足条件捕获事件
                    return true
                }
                return false;
            }
        });
    }

    shiftPercent = 0;//header位移百分比，默认为0

    footerShiftPercent = 0; // footer位移百分比
    /**
     * 渲染Header
     * @return {*}
     */
    renderHeader=()=>{
        const {renderHeader,HeaderComponent}=this.props;
        if(renderHeader){
            return renderHeader()
        }
        if(HeaderComponent){
            return HeaderComponent;
        }
        return <DefaultHeader/>
    }
    /**
     * 刷新时触发
     * @private
     */ 
    private _onSmartRefresh=(e:ReactNative.NativeSyntheticEvent<VoidEventData>)=>{
        let {onRefresh} = this.props;
        onRefresh && onRefresh(e);
    }
    /**
     * 下拉过程
     * @param event
     * @private
     */
    _onHeaderPulling=(event:ReactNative.NativeSyntheticEvent<OnHeaderEventData>)=>{
        this.shiftPercent = event.nativeEvent.percent;
        let {onHeaderPulling,onHeaderMoving} = this.props;
        onHeaderMoving && onHeaderMoving(event);
        onHeaderPulling && onHeaderPulling(event);
    }
    /**
     * 释放过程
     * @param event
     * @private
     */
    _onHeaderReleasing=(event:ReactNative.NativeSyntheticEvent<OnHeaderEventData>)=>{
        this.shiftPercent = event.nativeEvent.percent;
        let {onHeaderReleasing,onHeaderMoving} = this.props;
        onHeaderMoving && onHeaderMoving(event);
        onHeaderReleasing && onHeaderReleasing(event);
    }
    /**
     * 底部位移过程
     * @param event
     * @private
     */
    _onFooterMoving=(event:ReactNative.NativeSyntheticEvent<OnHeaderEventData>)=>{
        this.footerShiftPercent = event.nativeEvent.percent;
    }

    render() {
        const primaryColor = processColor(this.props.primaryColor)
        const nativeProps ={...this.props,...{
                onSmartRefresh:this._onSmartRefresh,
                onHeaderPulling:this._onHeaderPulling,
                onHeaderReleasing:this._onHeaderReleasing,
                onFooterMoving:this._onFooterMoving,
            }}
        if (primaryColor){
            nativeProps.primaryColor = primaryColor
        }


        // @ts-ignore
        if (typeof this.props.children?.props === 'object'){
            // @ts-ignore
            this.props.children.props.bounces = false
        }
        return (
            <RNCSmartRefreshLayout
                ref={(ref) => {
                    this.smartRefreshLayout = ref;
                }}
                {...nativeProps}
                {...this._panResponder?.panHandlers}
            >

                {this.props.children}
                {this.renderHeader()}
               

            </RNCSmartRefreshLayout>

        )
    }
}

export default SmartRefreshControl;
