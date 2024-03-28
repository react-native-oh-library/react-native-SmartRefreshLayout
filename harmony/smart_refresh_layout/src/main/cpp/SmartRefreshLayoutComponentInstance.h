#pragma once
#include "Animation.h"
#include "Props.h"
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#import "RNOH/arkui/ArkUINodeRegistry.h"
#import "RNOH/arkui/NativeNodeApi.h"
#include "PullToRefreshNode.h"
#include "EventEmitters.h"
#include <dlfcn.h>

namespace rnoh {
    class SmartRefreshLayoutComponentInstance : public CppComponentInstance, public PullToRefreshNodeDelegate, public TouchEventHandler {
    private:
        PullToRefreshNode m_pullToRefreshNode;
        StackNode m_headerStackNode;
        StackNode m_listStackNode;

        std::shared_ptr<const facebook::react::SmartRefreshLayoutEventEmitter> m_smartRefreshLayoutEventEmitter;

        bool overScrollBounce{true};
        bool enableRefresh{true};
        facebook::react::Float headerHeight{0.0};
        bool overScrollDrag{true};
        bool pureScroll{false};
        facebook::react::Float dragRate{0.5};
        facebook::react::Float maxDragRate{2.0};
        facebook::react::SharedColor primaryColor{};
        facebook::react::SmartRefreshLayoutAutoRefreshStruct autoRefresh{};
        bool isHeaderInserted{false}; // whether list child component inserted
        float trYTop{0.0};
        int32_t state{IS_FREE};
        int32_t touchYOld{0};
        int32_t touchYNew{0};
        int32_t downY{0};   // first down touch on Y
        int32_t offsetY{0}; // pan offset on Y
        Animation *animation{nullptr};

    public:
        SmartRefreshLayoutComponentInstance(Context context);

        void insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) override;

        void removeChild(ComponentInstance::Shared childComponentInstance) override;

        void setProps(facebook::react::Props::Shared props) override;

        void setNativeResponderBlocked(bool blocked) override;

        bool isComponentTop() override;

        PullToRefreshNode &getLocalRootArkUINode() override;

        void setEventEmitter(facebook::react::SharedEventEmitter eventEmitter) override;
    
        float getTranslateYOfRefresh(float newTranslateY);
        void onActionUpdate();
        void onActionEnd();
        void closeRefresh(float start, float target, int32_t duration);
        void finishRefresh();

        void onRefresh() override;
        void onHeaderPulling(const float &displayedHeaderHeight) override;
        void onHeaderReleasing(const float &displayedHeaderHeight) override;
        void onHeaderMoving(const float &displayedHeaderHeight) override;
        void onPullDownToRefresh() override;
        void onReleaseToRefresh() override;
        void onHeaderReleased() override;

        void handleCommand(std::string const &commandName, folly::dynamic const &args) override;
        void onTouchEvent(ArkUI_NodeTouchEvent e) override;
    };
} // namespace rnoh