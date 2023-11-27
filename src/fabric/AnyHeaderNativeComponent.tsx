import React from 'react';
import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent";
import type { ViewProps } from "react-native";
import type {HostComponent} from 'react-native';


export interface NativeProps extends ViewProps{
    primaryColor?:string
}
export default codegenNativeComponent<NativeProps>("RNCAnyHeader") as HostComponent<NativeProps>;

