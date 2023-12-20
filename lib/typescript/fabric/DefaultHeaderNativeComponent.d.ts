import { ViewProps } from "react-native";
import type { HostComponent } from "react-native";
interface NativeProps extends ViewProps {
    primaryColor?: string;
    accentColor?: string;
}
declare const _default: HostComponent<NativeProps>;
export default _default;
