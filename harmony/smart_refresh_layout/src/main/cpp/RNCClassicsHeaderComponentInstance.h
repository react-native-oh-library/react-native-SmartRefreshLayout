//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "HeaderNodeDelegate.h"
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#include "RNOH/arkui/TextNode.h"
#include "RNOH/arkui/ImageNode.h"
#include "ShadowNodes.h"

namespace rnoh {
    class RNCClassicsHeaderComponentInstance
        : public CppComponentInstance<facebook::react::RNCClassicsHeaderShadowNode>,
          public HeaderNodeDelegate {

    private:
        StackNode m_stackNode;
        ImageNode imageNode;
        ImageNode updateImageNode;
        TextNode textNode;
        TextNode timeTextNode;
        ArkUI_NodeHandle mColumnHandle;
        std::string primaryColor{""};

    public:
        RNCClassicsHeaderComponentInstance(Context context);
        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
        void onPropsChanged(SharedConcreteProps const &props) override;

        void finalizeUpdates() override;
        StackNode &getLocalRootArkUINode() override;
        void onRefreshStatusChange(int32_t status) override;
        std::string getDefaultHeaderBackGroundColor() { return primaryColor; }
        void setImageRotate(float angle);
    };
} // namespace rnoh
