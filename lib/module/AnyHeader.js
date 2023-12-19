function _extends() { _extends = Object.assign ? Object.assign.bind() : function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; }; return _extends.apply(this, arguments); }
import RCTAnyHeader from "./fabric/AnyHeaderNativeComponent";
import React from "react";
export class AnyHeader extends React.Component {
  render() {
    return /*#__PURE__*/React.createElement(RCTAnyHeader, _extends({}, this.props, {
      style: {
        height: 0
      }
    }), this.props.children);
  }
}
export default AnyHeader;
//# sourceMappingURL=AnyHeader.js.map