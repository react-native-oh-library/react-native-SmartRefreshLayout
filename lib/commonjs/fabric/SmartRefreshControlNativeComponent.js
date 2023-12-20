"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = exports.Commands = void 0;
var _codegenNativeCommands = _interopRequireDefault(require("react-native/Libraries/Utilities/codegenNativeCommands"));
var _codegenNativeComponent = _interopRequireDefault(require("react-native/Libraries/Utilities/codegenNativeComponent"));
function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }
// todo
// | WithDefault<boolean, false>;
var _default = exports.default = (0, _codegenNativeComponent.default)("SmartRefreshLayout"); // todo 类型
const Commands = exports.Commands = (0, _codegenNativeCommands.default)({
  supportedCommands: ["finishRefresh"]
});
//# sourceMappingURL=SmartRefreshControlNativeComponent.js.map