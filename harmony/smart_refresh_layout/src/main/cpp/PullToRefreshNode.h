#pragma once
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNOH/arkui/ArkUINode.h"
#include "PullToRefreshConfigurator.h"
#include "Animation.h"
#include "react/renderer/graphics/Color.h"

const int IS_FREE = 0;
const int IS_PULL_DOWN_1 = 11;
const int IS_PULL_DOWN_2 = 12;
const int IS_REFRESHING = 2;
const int IS_REFRESHED = 3;
const int IS_PULL_UP_1 = 41;
const int IS_PULL_UP_2 = 42;
const int IS_LOADING = 5;

namespace rnoh {

    class PullToRefreshNodeDelegate {
    public:
        virtual ~PullToRefreshNodeDelegate() = default;
        virtual void onRefresh(){};
        virtual void onHeaderPulling(const float &displayedHeaderHeight){};
        virtual void onHeaderReleasing(const float &displayedHeaderHeight){};
        virtual void onHeaderMoving(const float &displayedHeaderHeight){};
        virtual void onPullDownToRefresh(){};
        virtual void onHeaderReleased(){};
        virtual void onReleaseToRefresh(){};
        virtual bool  isComponentTop(){};
    };

    class PullToRefreshNode : public ArkUINode {
    protected:
        ArkUI_NodeHandle m_headerArkUINodeHandle;
        ArkUI_NodeHandle m_listArkUINodeHandle;
        PullToRefreshNodeDelegate *m_pullToRefreshNodeDelegate;
        PullToRefreshConfigurator refreshConfigurator{PullToRefreshConfigurator()};

    private:
        int32_t mWidth{0};
        int32_t mHeight{0};
        int32_t mHeightNumber{0};
        int32_t mWidthNumber{0};
        float trYTop{0.0};
        float trYBottom{0};
        int32_t state{IS_FREE};
        int32_t angle1{0};
        int32_t angle2{0};
        int32_t touchYOld{0};
        int32_t touchYNew{0};
        int32_t listOffsetOld{0};
        int32_t listOffsetNew{0};
        int32_t downY{0};   // first down touch on Y
        int32_t offsetY{0}; // pan offset on Y
        bool customRefresh;
        Animation *animation{nullptr};

        double cubicBezier(double t, double p0, double p1, double p2, double p3);

    public:
        PullToRefreshNode();
        ~PullToRefreshNode() override;

        float getDisplayedHeaderHeight() { return trYTop; }

        void insertChild(ArkUINode &child, std::size_t index);

        void removeChild(ArkUINode &child);

        void onNodeEvent(ArkUI_NodeEvent *event) override;

        void setPullToRefreshNodeDelegate(PullToRefreshNodeDelegate *pullToRefreshNodeDelegate);

        void onActionUpdate(ArkUI_NodeTouchPoint const &event);

        void onActionEnd();

        float getTranslateYOfRefresh(float newTranslateY);

        void animateWithCubicBezier(std::chrono::milliseconds duration, double startValue, double endValue,
                                    std::function<void(double)> callback);

        void closeRefresh();
        void finishRefresh();
        void onRefresh();
        void setHeaderHeight(float h);
        void setEnableRefresh(bool enable);
        void setMaxTranslate(float maxHeight);
        void setHeaderBackgroundColor(facebook::react::SharedColor &color);
        PullToRefreshConfigurator getPullToRefreshConfigurator() { return refreshConfigurator; }
    };

} // namespace rnoh