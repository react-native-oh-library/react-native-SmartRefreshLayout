import React from 'react';
import {ViewProps} from 'react-native';
import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent";
import type {
    WithDefault,
    Float,
    Int32
} from 'react-native/Libraries/Types/CodegenTypes';

interface NativeProps extends ViewProps{
    textColor?: string,
    text?: string,//暂时只支持英文
    fontSize?: WithDefault<Int32,25>,
    lineWidth?: Float,
    dropHeight?: Float,
}

export default codegenNativeComponent<NativeProps>("RNCStoreHouseHeader");
