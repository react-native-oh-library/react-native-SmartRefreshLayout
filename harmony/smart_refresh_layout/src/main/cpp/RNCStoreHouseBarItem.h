//
// Created on 2024/7/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_RNCSTOREHOUSEBARITEM_H
#define HARMONY_RNCSTOREHOUSEBARITEM_H
#include <cstdlib>
#include <ctime>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_pen.h>
#include <native_drawing/drawing_types.h>
#include <react/renderer/graphics/Color.h>
#include <glog/logging.h>
namespace rnoh {

typedef struct {
    float x;
    float y;
} PointF;


class RNCStoreHouseBarItem {

public:
    ~RNCStoreHouseBarItem() { OH_Drawing_PenDestroy(mPaint); }
    RNCStoreHouseBarItem(int i, PointF start, PointF end, facebook::react::SharedColor color, int lineWidth) {
        index = i;
        midPoint = {(start.x + end.x) / 2, (start.y + end.y) / 2};

        mCStartPoint = {start.x - midPoint.x, start.y - midPoint.y};
        mCEndPoint = {end.x - midPoint.x, end.y - midPoint.y};

        setColor(color);
        setLineWidth(lineWidth);
        OH_Drawing_PenSetAntiAlias(mPaint, true);
    }
    void setColor(facebook::react::SharedColor color) { OH_Drawing_PenSetColor(mPaint, *color); }
    void setLineWidth(int lineWidth) { OH_Drawing_PenSetWidth(mPaint, lineWidth); }

    void applyTransformation(float interpolatedTime) {
        float alpha = mFromAlpha;
        alpha = alpha + ((mToAlpha - alpha) * interpolatedTime);
        setAlpha(alpha);
    }
    void resetPosition(int horizontalRandomness) {
        srand((unsigned)time(NULL));
        translationX = rand() % horizontalRandomness;
    }
    void start(float fromAlpha, float toAlpha) {
        mFromAlpha = fromAlpha;
        mToAlpha = toAlpha;
    }
    void setAlpha(float alpha) { OH_Drawing_PenSetAlpha(mPaint, (int)(alpha * 255)); }
    void draw(OH_Drawing_Canvas *canvas) {
        OH_Drawing_CanvasAttachPen(canvas, mPaint);
        OH_Drawing_CanvasDrawLine(canvas, mCStartPoint.x, mCStartPoint.y, mCEndPoint.x, mCEndPoint.y);
        OH_Drawing_CanvasDetachPen(canvas);
    }

public:
    PointF midPoint;
    float translationX;
    int index;

private:
    OH_Drawing_Pen *mPaint{OH_Drawing_PenCreate()};
    float mFromAlpha{1.0f};
    float mToAlpha{0.4f};
    PointF mCStartPoint;
    PointF mCEndPoint;
};
} // namespace rnoh
#endif // HARMONY_RNCSTOREHOUSEBARITEM_H