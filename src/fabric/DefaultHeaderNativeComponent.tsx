import React from 'react';
import {ViewProps} from 'react-native';
import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent";
import type {HostComponent} from 'react-native';

interface NativeProps extends ViewProps{
    primaryColor?: string,
    accentColor?: string,
}

export default codegenNativeComponent<NativeProps>("RNCDefaultHeader") as HostComponent<NativeProps>;
