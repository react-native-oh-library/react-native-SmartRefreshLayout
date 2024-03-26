//
// Created on 2024/3/23.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCDefaultHeaderComponentInstance.h"

namespace rnoh {

    RNCDefaultHeaderComponentInstance::RNCDefaultHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}
    void RNCDefaultHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                        std::size_t index)  {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCDefaultHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &RNCDefaultHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

} // namespace rnoh