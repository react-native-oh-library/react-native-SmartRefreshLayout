#pragma once
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"

namespace rnoh {
    class RNCAnyHeaderComponentInstance : public CppComponentInstance {
    private:
        StackNode m_stackNode;

    public:
        RNCAnyHeaderComponentInstance(Context context, facebook::react::Tag tag);

        void insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) override;

        void removeChild(ComponentInstance::Shared childComponentInstance) override;

        StackNode &getLocalRootArkUINode() override;
    };
} // namespace rnoh