"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.StoreHouseHeader = exports.SmartRefreshLayout = exports.DefaultHeader = exports.ClassicsHeader = exports.AnyHeader = void 0;
var _react = require("react");
function _defineProperty(obj, key, value) { key = _toPropertyKey(key); if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }
function _toPropertyKey(t) { var i = _toPrimitive(t, "string"); return "symbol" == typeof i ? i : String(i); }
function _toPrimitive(t, r) { if ("object" != typeof t || !t) return t; var e = t[Symbol.toPrimitive]; if (void 0 !== e) { var i = e.call(t, r || "default"); if ("object" != typeof i) return i; throw new TypeError("@@toPrimitive must return a primitive value."); } return ("string" === r ? String : Number)(t); }
class SmartRefreshLayout extends _react.Component {
  constructor(...args) {
    super(...args);
    _defineProperty(this, "finishRefresh", void 0);
  }
}
exports.SmartRefreshLayout = SmartRefreshLayout;
class ClassicsHeader extends _react.Component {}
exports.ClassicsHeader = ClassicsHeader;
class DefaultHeader extends _react.Component {}
exports.DefaultHeader = DefaultHeader;
class StoreHouseHeader extends _react.Component {}
exports.StoreHouseHeader = StoreHouseHeader;
class AnyHeader extends _react.Component {}
exports.AnyHeader = AnyHeader;
//# sourceMappingURL=index.d.js.map