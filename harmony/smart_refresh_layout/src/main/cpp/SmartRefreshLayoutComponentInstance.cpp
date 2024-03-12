#include "SmartRefreshLayoutComponentInstance.h"
#include <folly/dynamic.h>

namespace rnoh {

    SmartRefreshLayoutComponentInstance::SmartRefreshLayoutComponentInstance(Context context, facebook::react::Tag tag)
        : CppComponentInstance(std::move(context), tag) {
        m_pullToRefreshNode.setPullToRefreshNodeDelegate(this);
    }

    void SmartRefreshLayoutComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                          std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        if (!isListInserted) {
            m_pullToRefreshNode.insertChild(childComponentInstance->getLocalRootArkUINode(), isListInserted);
            isListInserted = true;
        } else {
            m_pullToRefreshNode.insertChild(childComponentInstance->getLocalRootArkUINode(), isListInserted);
        }
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::insertChild> childComponentInstance"
                  << childComponentInstance;
    }

    void SmartRefreshLayoutComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_pullToRefreshNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    PullToRefreshNode &SmartRefreshLayoutComponentInstance::getLocalRootArkUINode() { return m_pullToRefreshNode; }


    void SmartRefreshLayoutComponentInstance::setProps(facebook::react::Props::Shared props) {
        ComponentInstance::setProps(props);
        auto refreshProps = std::dynamic_pointer_cast<const facebook::react::SmartRefreshLayoutProps>(props);
        if (refreshProps == nullptr) {
            return;
        }
        // TODO: refreshProps attributes
        headerHeight = refreshProps->headerHeight;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> autoRefresh.refresh:"
                  << refreshProps->autoRefresh.refresh;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> dragRate:" << refreshProps->dragRate;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> enableRefresh:"
                  << refreshProps->enableRefresh;
    }

    void SmartRefreshLayoutComponentInstance::setEventEmitter(facebook::react::SharedEventEmitter eventEmitter) {
        ComponentInstance::setEventEmitter(eventEmitter);
        auto smartRefreshLayoutEventEmitter =
            std::dynamic_pointer_cast<const facebook::react::SmartRefreshLayoutEventEmitter>(eventEmitter);
        if (smartRefreshLayoutEventEmitter == nullptr) {
            return;
        }
        m_smartRefreshLayoutEventEmitter = smartRefreshLayoutEventEmitter;
    };

    void SmartRefreshLayoutComponentInstance::onRefresh() { m_smartRefreshLayoutEventEmitter->onRefresh({}); };

    void SmartRefreshLayoutComponentInstance::onHeaderPulling(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_smartRefreshLayoutEventEmitter->onHeaderPulling({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::onHeaderReleasing(const float &displayedHeaderHeight) {
        facebook::react::Float percent = displayedHeaderHeight / headerHeight;
        m_smartRefreshLayoutEventEmitter->onHeaderReleasing({percent, displayedHeaderHeight, headerHeight});
    };

    void SmartRefreshLayoutComponentInstance::handleCommand(std::string const &commandName, folly::dynamic const &args){
        if (commandName == "finishRefresh" && args.isArray() && args.size() == 2) {
            auto delayed = args[0];
            auto success = args[1];
            if (delayed != INFINITY) {
                if (delayed >= 0) {
                    m_pullToRefreshNode.getPullToRefreshConfigurator().setFinishDelay(delayed.asInt());
                } else {
                    m_pullToRefreshNode.getPullToRefreshConfigurator().setFinishDelay(0);
                }
            } else {
                m_pullToRefreshNode.getPullToRefreshConfigurator().setFinishDelay(500);
            }
        }
    };

} // namespace rnoh
