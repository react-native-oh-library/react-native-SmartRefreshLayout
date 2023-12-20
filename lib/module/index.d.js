function _defineProperty(obj, key, value) { key = _toPropertyKey(key); if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }
function _toPropertyKey(t) { var i = _toPrimitive(t, "string"); return "symbol" == typeof i ? i : String(i); }
function _toPrimitive(t, r) { if ("object" != typeof t || !t) return t; var e = t[Symbol.toPrimitive]; if (void 0 !== e) { var i = e.call(t, r || "default"); if ("object" != typeof i) return i; throw new TypeError("@@toPrimitive must return a primitive value."); } return ("string" === r ? String : Number)(t); }
import { Component } from "react";
export class SmartRefreshLayout extends Component {
  constructor(...args) {
    super(...args);
    _defineProperty(this, "finishRefresh", void 0);
  }
}
export class ClassicsHeader extends Component {}
export class DefaultHeader extends Component {}
export class StoreHouseHeader extends Component {}
export class AnyHeader extends Component {}
//# sourceMappingURL=index.d.js.map