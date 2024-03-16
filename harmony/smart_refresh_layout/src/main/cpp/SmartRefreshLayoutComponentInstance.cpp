#include "SmartRefreshLayoutComponentInstance.h"
#include "Singleton.h"
#include <folly/dynamic.h>

namespace rnoh {

    SmartRefreshLayoutComponentInstance::SmartRefreshLayoutComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        Singleton::getInstance().pullNode.setPullToRefreshNodeDelegate(this);
    }

    void SmartRefreshLayoutComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                          std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        if (!isListInserted) {
            Singleton::getInstance().pullNode.insertChild(childComponentInstance->getLocalRootArkUINode(),
                                                          isListInserted);
            isListInserted = true;
        } else {
            Singleton::getInstance().pullNode.insertChild(childComponentInstance->getLocalRootArkUINode(),
                                                          isListInserted);
        }
    }

    void SmartRefreshLayoutComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        Singleton::getInstance().pullNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    PullToRefreshNode &SmartRefreshLayoutComponentInstance::getLocalRootArkUINode() {
        return Singleton::getInstance().pullNode;
    }


    void SmartRefreshLayoutComponentInstance::setProps(facebook::react::Props::Shared props) {
        ComponentInstance::setProps(props);
        auto refreshProps = std::dynamic_pointer_cast<const facebook::react::SmartRefreshLayoutProps>(props);
        if (refreshProps == nullptr) {
            return;
        }
        // TODO: refreshProps attributes
        headerHeight = refreshProps->headerHeight;

        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> headerHeight:" << headerHeight;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> autoRefresh.refresh:"
                  << refreshProps->autoRefresh.refresh;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> dragRate:" << refreshProps->dragRate;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> enableRefresh:"
                  << refreshProps->enableRefresh;
        LOG(INFO) << "[clx] <SmartRefreshLayoutComponentInstance::setProps> refreshProps:"
                  << refreshProps->primaryColor;

        Singleton::getInstance().pullNode.setEnableRefresh(refreshProps->enableRefresh);
        //         Singleton::getInstance().pullNode.setMaxTranslate(refreshProps->maxDragRate);
        //         Singleton::getInstance().pullNode.setHeaderHeight(refreshProps->headerHeight);
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

    void SmartRefreshLayoutComponentInstance::handleCommand(std::string const &commandName,
                                                            folly::dynamic const &args) {
        if (commandName == "finishRefresh" && args.isArray() && args.size() == 2) {
            auto delayed = args[0];
            auto success = args[1];
            if (delayed != INFINITY) {
                if (delayed >= 0) {
                    Singleton::getInstance().pullNode.getPullToRefreshConfigurator().setFinishDelay(delayed.asInt());
                } else {
                    Singleton::getInstance().pullNode.getPullToRefreshConfigurator().setFinishDelay(0);
                }
            } else {
                Singleton::getInstance().pullNode.getPullToRefreshConfigurator().setFinishDelay(500);
            }
            Singleton::getInstance().pullNode.finishRefresh();
        }
    };

} // namespace rnoh
