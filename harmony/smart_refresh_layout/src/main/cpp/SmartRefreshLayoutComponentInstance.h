#pragma once
#include "Props.h"
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#import "RNOH/arkui/ArkUINodeRegistry.h"
#import "RNOH/arkui/NativeNodeApi.h"
#include "PullToRefreshNode.h"
#include "EventEmitters.h"

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

    public:
        SmartRefreshLayoutComponentInstance(Context context);

        void onTouchEvent(ArkUI_NodeTouchEvent e) override;

        void insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) override;

        void removeChild(ComponentInstance::Shared childComponentInstance) override;

        void setProps(facebook::react::Props::Shared props) override;
    
        bool  isComponentTop() override;
    
        void setParent(ComponentInstance::Shared parent) override;
    
        PullToRefreshNode &getLocalRootArkUINode() override;

        void setEventEmitter(facebook::react::SharedEventEmitter eventEmitter) override;

        void onRefresh() override;

        void onHeaderPulling(const float &displayedHeaderHeight) override;

        void onHeaderReleasing(const float &displayedHeaderHeight) override;
        void onHeaderMoving(const float &displayedHeaderHeight) override;
        void onPullDownToRefresh() override;
        void onReleaseToRefresh() override;
        void onHeaderReleased() override;
        void handleCommand(std::string const &commandName, folly::dynamic const &args) override;
    };
} // namespace rnoh