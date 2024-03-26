//
// Created on 2024/3/23.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#include "ShadowNodes.h"

namespace rnoh {
    class RNCDefaultHeaderComponentInstance : public CppComponentInstance<facebook::react::RNCDefaultHeaderShadowNode> {

    private:
        StackNode m_stackNode;

    public:
        RNCDefaultHeaderComponentInstance(Context context);

        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

        StackNode &getLocalRootArkUINode() override;
    };
} // namespace rnoh