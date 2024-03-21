#include "RNCAnyHeaderComponentInstance.h"

namespace rnoh {

    RNCAnyHeaderComponentInstance::RNCAnyHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}

    void RNCAnyHeaderComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                    std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCAnyHeaderComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &RNCAnyHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

} // namespace rnoh
