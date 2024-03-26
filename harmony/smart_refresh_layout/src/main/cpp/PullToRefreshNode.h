#pragma once
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNOH/arkui/ArkUINode.h"
#include "PullToRefreshConfigurator.h"
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
        virtual bool isComponentTop(){};
    };

    class PullToRefreshNode : public ArkUINode {
    protected:
        ArkUI_NodeHandle m_headerArkUINodeHandle;
        ArkUI_NodeHandle m_listArkUINodeHandle;
        PullToRefreshNodeDelegate *m_pullToRefreshNodeDelegate;
        PullToRefreshConfigurator refreshConfigurator{PullToRefreshConfigurator()};
    
    public:
        PullToRefreshNode();
        ~PullToRefreshNode() override;
    
        void insertChild(ArkUINode &child, std::size_t index);

        void removeChild(ArkUINode &child);
    
        void setPullToRefreshNodeDelegate(PullToRefreshNodeDelegate *pullToRefreshNodeDelegate);
        
        void setHeaderHeight(float h);
        void setEnableRefresh(bool enable);
        void setMaxTranslate(float maxHeight);
        void setHeaderBackgroundColor(facebook::react::SharedColor &color);
        PullToRefreshConfigurator getPullToRefreshConfigurator() { return refreshConfigurator; }
    };

} // namespace rnoh