#include "RNCAnyHeaderComponentInstance.h"
#include "Singleton.h"

namespace rnoh {

    RNCAnyHeaderComponentInstance::RNCAnyHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}

    void RNCAnyHeaderComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                    std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        LOG(INFO) << "[clx] <sss PullToRefreshNode33333------------ ";
      //  m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
        Singleton::getInstance().pullNode.insertHeaderChild(childComponentInstance->getLocalRootArkUINode());
    }

    void RNCAnyHeaderComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &RNCAnyHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

} // namespace rnoh
