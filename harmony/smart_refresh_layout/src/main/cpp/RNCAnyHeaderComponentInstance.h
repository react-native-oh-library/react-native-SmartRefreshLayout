#pragma once
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "SmartStackNode.h"

namespace rnoh {
    class RNCAnyHeaderComponentInstance : public CppComponentInstance<facebook::react::RNCAnyHeaderShadowNode>  {
    private:
        SmartStackNode m_stackNode;

    public:
        RNCAnyHeaderComponentInstance(Context context);

        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

        SmartStackNode &getLocalRootArkUINode() override;
        
         void finalizeUpdates() override;
    };
} // namespace rnoh