function _extends() { _extends = Object.assign ? Object.assign.bind() : function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; }; return _extends.apply(this, arguments); }
function _defineProperty(obj, key, value) { key = _toPropertyKey(key); if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }
function _toPropertyKey(t) { var i = _toPrimitive(t, "string"); return "symbol" == typeof i ? i : String(i); }
function _toPrimitive(t, r) { if ("object" != typeof t || !t) return t; var e = t[Symbol.toPrimitive]; if (void 0 !== e) { var i = e.call(t, r || "default"); if ("object" != typeof i) return i; throw new TypeError("@@toPrimitive must return a primitive value."); } return ("string" === r ? String : Number)(t); }
import React from "react";
import { findNodeHandle, NativeModules, Platform, PanResponder, processColor } from "react-native";
import RNCSmartRefreshLayout, { Commands as SmartRefreshControlCommands } from "./fabric/SmartRefreshControlNativeComponent";
import DefaultHeader from "./fabric/DefaultHeaderNativeComponent";
const SPModule = Platform.OS === "android" ? NativeModules.SpinnerStyleModule : {};
export class SmartRefreshControl extends React.Component {
  constructor(...args) {
    super(...args);
    _defineProperty(this, "_panResponder", null);
    _defineProperty(this, "smartRefreshLayout", null);
    /**
     * 参数格式为{delayed:number,success:bool}
     * delayed:延迟刷新
     * success:是否刷新成功
     * @param params
     */
    _defineProperty(this, "finishRefresh", ({
      delayed = -1,
      success = true
    } = {
      delayed: -1,
      success: true
    }) => {
      // this.dispatchCommand('finishRefresh',[delayed,success])
      if (this.smartRefreshLayout) {
        SmartRefreshControlCommands.finishRefresh(this.smartRefreshLayout, delayed, success);
      }
    });
    _defineProperty(this, "findNode", () => {
      return findNodeHandle(this.smartRefreshLayout);
    });
    _defineProperty(this, "shiftPercent", 0);
    //header位移百分比，默认为0
    _defineProperty(this, "footerShiftPercent", 0);
    // footer位移百分比
    /**
     * 渲染Header
     * @return {*}
     */
    _defineProperty(this, "renderHeader", () => {
      const {
        renderHeader,
        HeaderComponent
      } = this.props;
      if (renderHeader) {
        return renderHeader();
      }
      if (HeaderComponent) {
        return HeaderComponent;
      }
      return /*#__PURE__*/React.createElement(DefaultHeader, null);
    });
    /**
     * 刷新时触发
     * @private
     */
    _defineProperty(this, "_onSmartRefresh", e => {
      let {
        onRefresh
      } = this.props;
      onRefresh && onRefresh(e);
    });
    /**
     * 下拉过程
     * @param event
     * @private
     */
    _defineProperty(this, "_onHeaderPulling", event => {
      this.shiftPercent = event.nativeEvent.percent;
      let {
        onHeaderPulling,
        onHeaderMoving
      } = this.props;
      onHeaderMoving && onHeaderMoving(event);
      onHeaderPulling && onHeaderPulling(event);
    });
    /**
     * 释放过程
     * @param event
     * @private
     */
    _defineProperty(this, "_onHeaderReleasing", event => {
      this.shiftPercent = event.nativeEvent.percent;
      let {
        onHeaderReleasing,
        onHeaderMoving
      } = this.props;
      onHeaderMoving && onHeaderMoving(event);
      onHeaderReleasing && onHeaderReleasing(event);
    });
    /**
     * 底部位移过程
     * @param event
     * @private
     */
    _defineProperty(this, "_onFooterMoving", event => {
      this.footerShiftPercent = event.nativeEvent.percent;
    });
  }
  componentWillMount() {
    this._panResponder = PanResponder.create({
      onMoveShouldSetPanResponderCapture: (evt, gestureState) => {
        if (this.shiftPercent >= 0.039 || this.footerShiftPercent >= 0.068) {
          //满足条件捕获事件
          return true;
        }
        return false;
      }
    });
  }
  render() {
    var _this$props$children, _this$_panResponder;
    const primaryColor = processColor(this.props.primaryColor);
    const nativeProps = {
      ...this.props,
      ...{
        onSmartRefresh: this._onSmartRefresh,
        onHeaderPulling: this._onHeaderPulling,
        onHeaderReleasing: this._onHeaderReleasing,
        onFooterMoving: this._onFooterMoving
      }
    };
    if (primaryColor) {
      nativeProps.primaryColor = primaryColor;
    }

    // @ts-ignore
    if (typeof ((_this$props$children = this.props.children) === null || _this$props$children === void 0 ? void 0 : _this$props$children.props) === "object" && Platform.OS === 'harmony') {
      // @ts-ignore
      this.props.children.props.bounces = false;
    }
    return /*#__PURE__*/React.createElement(RNCSmartRefreshLayout, _extends({
      ref: ref => {
        this.smartRefreshLayout = ref;
      }
    }, nativeProps, (_this$_panResponder = this._panResponder) === null || _this$_panResponder === void 0 ? void 0 : _this$_panResponder.panHandlers), this.props.children, this.renderHeader());
  }
}
_defineProperty(SmartRefreshControl, "constants", {
  TRANSLATE: SPModule.translate,
  SCALE: SPModule.scale,
  FIX_BEHIND: SPModule.fixBehind,
  FIX_FRONT: SPModule.fixFront,
  MATCH_LAYOUT: SPModule.matchLayout
});
export default SmartRefreshControl;
//# sourceMappingURL=SmartRefreshControl.js.map