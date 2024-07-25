#include "RNCStoreHouseHeaderNode.h"
#include <glog/logging.h>
#include <arkui/native_node.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_color.h>
#include <native_drawing/drawing_color.h>
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_types.h>
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNCStoreHousePath.h"
#include "SmartUtils.h"

namespace rnoh {
RNCStoreHouseHeaderNode::RNCStoreHouseHeaderNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_CUSTOM)) {
    canvasCallback_ = new StoreHouseCanvasCallback();
    // 设置自定义回调。注册onDraw
    canvasCallback_->callback = [this](ArkUI_NodeCustomEvent *event) {
        auto type = OH_ArkUI_NodeCustomEvent_GetEventType(event);
        switch (type) {
        case ARKUI_NODE_CUSTOM_EVENT_ON_DRAW:
            OnDraw(event);
            break;
        case ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE: {
            int32_t width = getSavedWidth();
            int32_t height = getSavedHeight();
            maybeThrow(NativeNodeApi::getInstance()->setMeasuredSize(m_nodeHandle, width,
                                                                     mDropHeight + delegate->getVp2Px(40)));
        } break;
        default:
            break;
        }
    };
    eventReceiver = [](ArkUI_NodeCustomEvent *event) {
        int32_t targetId = OH_ArkUI_NodeCustomEvent_GetEventTargetId(event);
        if (targetId == 1001 || targetId == 1002) {
            auto *userData = reinterpret_cast<StoreHouseCanvasCallback *>(OH_ArkUI_NodeCustomEvent_GetUserData(event));
            if (userData != nullptr && userData->callback != nullptr) {
                userData->callback(event);
            }
        }
    };

    maybeThrow(NativeNodeApi::getInstance()->addNodeCustomEventReceiver(m_nodeHandle, eventReceiver));
    maybeThrow(NativeNodeApi::getInstance()->registerNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                                                     1001, canvasCallback_));
    maybeThrow(NativeNodeApi::getInstance()->registerNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW,
                                                                     1002, canvasCallback_));
}

RNCStoreHouseHeaderNode::~RNCStoreHouseHeaderNode() {
    NativeNodeApi::getInstance()->removeNodeCustomEventReceiver(m_nodeHandle, eventReceiver);
    NativeNodeApi::getInstance()->unregisterNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    NativeNodeApi::getInstance()->unregisterNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    OH_Drawing_MatrixDestroy(mMatrix);
    mItemList.clear();
    delete canvasCallback_;
    canvasCallback_ = nullptr;
    canvas = nullptr;
    mMatrix = nullptr;
}
void RNCStoreHouseHeaderNode::setStoreHouseNodeDelegate(StoreHouseNodeDelegate *storeHouseNodeDelegate) {
    delegate = storeHouseNodeDelegate;
}
void RNCStoreHouseHeaderNode::initStoreHouse() { initWithString(mText, mFontSize); }
void RNCStoreHouseHeaderNode::setText(std::string text) { mText = text; }
void RNCStoreHouseHeaderNode::setTextColor(std::string textColor) { mTextColor = SmartUtils::parseColor(textColor); }
void RNCStoreHouseHeaderNode::setFontSize(int size) { mFontSize = size; }
void RNCStoreHouseHeaderNode::setLineWidth(float width) { mLineWidth = delegate->getVp2Px(width); }
void RNCStoreHouseHeaderNode::setDropHeight(float dropHeight) { mDropHeight = dropHeight; }
void RNCStoreHouseHeaderNode::initWithString(std::string str, int fontSize) {
    std::vector<std::vector<float>> pointList = RNCStoreHousePath::getPath(str, fontSize * 0.01f, 14);
    initWithPointList(pointList);
}
void RNCStoreHouseHeaderNode::setProgress(float progress) {
    mProgress = (progress / 69) * 0.8;
    markDirty();
}

bool RNCStoreHouseHeaderNode::isInEditMode() { return true; }
void RNCStoreHouseHeaderNode::initWithPointList(std::vector<std::vector<float>> pointList) {
    float drawWidth = 0;
    float drawHeight = 0;
    bool shouldLayout = mItemList.size() > 0;
    if (shouldLayout) {
        mItemList.clear();
    }

    for (int i = 0; i < pointList.size(); i++) {
        std::vector<float> line = pointList[i];
        PointF startPoint = {delegate->getVp2Px(line[0]) * mScale, delegate->getVp2Px(line[1]) * mScale};
        PointF endPoint = {delegate->getVp2Px(line[2]) * mScale, delegate->getVp2Px(line[3]) * mScale};

        drawWidth = std::max(drawWidth, startPoint.x);
        drawWidth = std::max(drawWidth, endPoint.x);

        drawHeight = std::max(drawHeight, startPoint.y);
        drawHeight = std::max(drawHeight, endPoint.y);
        auto item = new RNCStoreHouseBarItem(i, startPoint, endPoint, mTextColor, mLineWidth);
        item->resetPosition(mHorizontalRandomness);
        mItemList.push_back(item);
    }

    mDrawZoneWidth = (int)std::ceil(drawWidth);
    mDrawZoneHeight = (int)std::ceil(drawHeight);
    if (shouldLayout) {
        markDirty();
    }
}
void RNCStoreHouseHeaderNode::OnDraw(ArkUI_NodeCustomEvent *event) {
    auto *drawContext = OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(event);
    canvas = reinterpret_cast<OH_Drawing_Canvas *>(OH_ArkUI_DrawContext_GetCanvas(drawContext));
    auto height = OH_Drawing_CanvasGetHeight(canvas);
    auto width = OH_Drawing_CanvasGetWidth(canvas);
    mOffsetX = (width - mDrawZoneWidth) / 2;
    mOffsetY = (height - mDrawZoneHeight) / 4;
    mDropHeight = height / 2;

    OH_Drawing_CanvasSave(canvas);
    int c1 = OH_Drawing_CanvasGetSaveCount(canvas);
    int len = mItemList.size();
    float progress = isInEditMode() ? 1 : mProgress;
    for (int i = 0; i < len; i++) {

        OH_Drawing_CanvasSave(canvas);
        RNCStoreHouseBarItem *storeHouseBarItem = mItemList[i];
        float offsetX = mOffsetX + storeHouseBarItem->midPoint.x;
        float offsetY = mOffsetY + storeHouseBarItem->midPoint.y;

        if (mIsInLoading) {
            //             storeHouseBarItem.getTransformation(getDrawingTime(), mTransformation);
            //             canvas.translate(offsetX, offsetY);
        } else {

            if (progress == 0) {
                storeHouseBarItem->resetPosition(mHorizontalRandomness);
                continue;
            }

            float startPadding = (1 - mInternalAnimationFactor) * i / len;
            float endPadding = 1 - mInternalAnimationFactor - startPadding;

            // done
            if (progress == 1 || progress >= 1 - endPadding) {
                OH_Drawing_CanvasTranslate(canvas, offsetX, offsetY);
                storeHouseBarItem->setAlpha(mBarDarkAlpha);
            } else {
                float realProgress;
                if (progress <= startPadding) {
                    realProgress = 0;
                } else {
                    realProgress = std::min(1, (int)((progress - startPadding) / mInternalAnimationFactor));
                }
                offsetX += storeHouseBarItem->translationX * (1 - realProgress);
                offsetY += -mDropHeight * (1 - realProgress);
                OH_Drawing_MatrixReset(mMatrix);
                OH_Drawing_MatrixPostRotate(mMatrix, 360 * realProgress, width / 2, height / 2);
                OH_Drawing_MatrixPostScale(mMatrix, realProgress, realProgress, width / 2, height / 2);
                OH_Drawing_MatrixPostTranslate(mMatrix, offsetX, offsetY);
                storeHouseBarItem->setAlpha(mBarDarkAlpha * realProgress);
                OH_Drawing_CanvasConcatMatrix(canvas, mMatrix);
            }
        }
        storeHouseBarItem->draw(canvas);
        OH_Drawing_CanvasRestore(canvas);
    }
    if (mIsInLoading) {
        markDirty();
    }
    OH_Drawing_CanvasRestoreToCount(canvas, c1);
}

} // namespace rnoh