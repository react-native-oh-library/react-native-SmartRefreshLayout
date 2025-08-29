import React, { Component } from "react";
import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent";
import type { ViewProps } from "react-native";
import type { HostComponent } from "react-native";

interface NativeProps extends ViewProps {
  primaryColor?: string;
  accentColor?: string;
}

export default codegenNativeComponent<NativeProps>(
  "RNCClassicsHeader",
) as HostComponent<NativeProps>;
