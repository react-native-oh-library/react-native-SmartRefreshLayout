/// <reference types="react-native/types/modules/codegen" />
import { ViewProps } from "react-native";
import type { WithDefault, Float, Int32 } from "react-native/Libraries/Types/CodegenTypes";
interface NativeProps extends ViewProps {
    textColor?: string;
    text?: string;
    fontSize?: WithDefault<Int32, 25>;
    lineWidth?: Float;
    dropHeight?: Float;
}
declare const _default: import("react-native/Libraries/Utilities/codegenNativeComponent").NativeComponentType<NativeProps>;
export default _default;
