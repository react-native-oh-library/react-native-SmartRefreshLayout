//
// Created on 2024/3/23.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCDefaultHeaderComponentInstance.h"

namespace rnoh {

    RNCDefaultHeaderComponentInstance::RNCDefaultHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}
    void RNCDefaultHeaderComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                        std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCDefaultHeaderComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &RNCDefaultHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

} // namespace rnoh