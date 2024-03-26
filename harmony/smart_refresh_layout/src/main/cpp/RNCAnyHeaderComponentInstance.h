#pragma once
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#include "ShadowNodes.h"

namespace rnoh {
    class RNCAnyHeaderComponentInstance : public CppComponentInstance<facebook::react::RNCAnyHeaderShadowNode>  {
    private:
        StackNode m_stackNode;

    public:
        RNCAnyHeaderComponentInstance(Context context);

        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

        StackNode &getLocalRootArkUINode() override;
    };
} // namespace rnoh