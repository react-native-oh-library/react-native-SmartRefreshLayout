//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "HeaderNodeDelegate.h"
#include "RNCStoreHouseHeaderNode.h"
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
namespace rnoh {
class RNCStoreHouseHeaderComponentInstance
    : public CppComponentInstance<facebook::react::RNCStoreHouseHeaderShadowNode>,
      public StoreHouseNodeDelegate,
      public HeaderNodeDelegate {

private:
    RNCStoreHouseHeaderNode m_storeHouseNode;


public:
    RNCStoreHouseHeaderComponentInstance(Context context);
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    void onPropsChanged(SharedConcreteProps const &props) override;
    RNCStoreHouseHeaderNode &getLocalRootArkUINode() override;
    float getVp2Px(float v) override;
    facebook::react::SharedColor GetPrimaryColor() override;
    void onHeaderMove(float dur) override;
};
} // namespace rnoh