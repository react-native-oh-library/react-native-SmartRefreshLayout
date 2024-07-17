#pragma once
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNOH/arkui/ArkUINode.h"
#include "PullToRefreshConfigurator.h"
#include "react/renderer/graphics/Color.h"
#include "RNCStoreHouseBarItem.h"
#include <native_drawing/drawing_matrix.h>
namespace rnoh {
class StoreHouseNodeDelegate {
public:
    virtual ~StoreHouseNodeDelegate() = default;
    virtual float getVp2Px(float v){};
};

struct StoreHouseCanvasCallback {
    std::function<void(ArkUI_NodeCustomEvent *event)> callback;
};
class RNCStoreHouseHeaderNode : public ArkUINode {
private:
    StoreHouseCanvasCallback *canvasCallback_{nullptr};
    void (*eventReceiver)(ArkUI_NodeCustomEvent *event);
    facebook::react::SharedColor mTextColor{};
    std::string mText{"StoreHouse"};
    int mFontSize{25};
    float mLineWidth{0.0};
    float mDropHeight{0.0};
    std::vector<RNCStoreHouseBarItem *> mItemList;
    float mScale{1};
    int mHorizontalRandomness{-1};
    int mDrawZoneWidth{0};
    int mDrawZoneHeight{0};
    int mOffsetX{0};
    int mOffsetY{0};
    float mProgress{0};
    bool mIsInLoading{false};
    float mInternalAnimationFactor{0.7f};
    float mBarDarkAlpha{0.4f};
    OH_Drawing_Matrix *mMatrix{OH_Drawing_MatrixCreate()};
    OH_Drawing_Canvas *canvas;
    StoreHouseNodeDelegate *delegate;

public:
    RNCStoreHouseHeaderNode();
    ~RNCStoreHouseHeaderNode() override;

    void setStoreHouseNodeDelegate(StoreHouseNodeDelegate *delegate);
    void OnDraw(ArkUI_NodeCustomEvent *event);
    void setText(std::string text);
    void setTextColor(std::string textColor);
    void setFontSize(int size);
    void setLineWidth(float width);
    void setDropHeight(float dropHeight);
    void initStoreHouse();
    void setProgress(float progress);

private:
    void initWithString(std::string str, int fontSize);
    void initWithPointList(std::vector<std::vector<float>>);
    bool isInEditMode();
};

} // namespace rnoh