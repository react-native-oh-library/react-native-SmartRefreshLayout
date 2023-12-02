import RCTAnyHeader, {
  NativeProps as AnyHeaderProps,
} from "./fabric/AnyHeaderNativeComponent";
import React from "react";

export class AnyHeader extends React.Component<AnyHeaderProps> {
  render() {
    return (
      <RCTAnyHeader {...this.props} style={{ height: 0 }}>
        {this.props.children}
      </RCTAnyHeader>
    );
  }
}

export default AnyHeader;
