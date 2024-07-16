#pragma once
#include "HeaderNodeDelegate.h"
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "SmartStackNode.h"
#include <string>

namespace rnoh {
class RNCAnyHeaderComponentInstance : public CppComponentInstance<facebook::react::RNCAnyHeaderShadowNode>,
                                      public HeaderNodeDelegate {
private:
    SmartStackNode m_stackNode;
    std::string backColor{""};

public:
    RNCAnyHeaderComponentInstance(Context context);

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    void onPropsChanged(SharedConcreteProps const &props) override;
    SmartStackNode &getLocalRootArkUINode() override;
    facebook::react::SharedColor GetPrimaryColor() override;
    void finalizeUpdates() override;
};
} // namespace rnoh