#include "RNCAnyHeaderComponentInstance.h"

namespace rnoh {

    RNCAnyHeaderComponentInstance::RNCAnyHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}

    void RNCAnyHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                        std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCAnyHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &RNCAnyHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

} // namespace rnoh