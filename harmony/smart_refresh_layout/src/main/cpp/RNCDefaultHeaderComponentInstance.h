//
// Created on 2024/3/23.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#include "RNOH/arkui/TextNode.h"
#include "RNOH/arkui/ImageNode.h"
#include "RNOH/arkui/LoadingProgressNode.h"
#include "ShadowNodes.h"

namespace rnoh {
    class RNCDefaultHeaderComponentInstance : public CppComponentInstance<facebook::react::RNCDefaultHeaderShadowNode> {

    private:
        StackNode m_stackNode;
        ImageNode imageNode;
        TextNode textNode;
        LoadingProgressNode progressNode;
        ArkUI_NodeHandle mColumnHandle;
        std::string primaryColor{""};

    public:
        RNCDefaultHeaderComponentInstance(Context context);
        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
        void onPropsChanged(SharedConcreteProps const &props) override;

        void finalizeUpdates() override;
        StackNode &getLocalRootArkUINode() override;
        void onRefreshStatusChange(int32_t status);
        std::string getDefaultHeaderBackGroundColor() { return primaryColor; }
    };
} // namespace rnoh