#pragma once
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNOH/arkui/ArkUINode.h"
#include "PullToRefreshConfigurator.h"
#include "react/renderer/graphics/Color.h"

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
        void setHeaderBackgroundColor(facebook::react::SharedColor const &color);
        PullToRefreshConfigurator getPullToRefreshConfigurator() { return refreshConfigurator; }
    };

} // namespace rnoh