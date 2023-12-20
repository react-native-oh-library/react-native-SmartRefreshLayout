"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = exports.AnyHeader = void 0;
var _AnyHeaderNativeComponent = _interopRequireDefault(require("./fabric/AnyHeaderNativeComponent"));
var _react = _interopRequireDefault(require("react"));
function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }
function _extends() { _extends = Object.assign ? Object.assign.bind() : function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; }; return _extends.apply(this, arguments); }
class AnyHeader extends _react.default.Component {
  render() {
    return /*#__PURE__*/_react.default.createElement(_AnyHeaderNativeComponent.default, _extends({}, this.props, {
      style: {
        height: 0
      }
    }), this.props.children);
  }
}
exports.AnyHeader = AnyHeader;
var _default = exports.default = AnyHeader;
//# sourceMappingURL=AnyHeader.js.map