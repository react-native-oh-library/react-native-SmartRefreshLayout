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
#include "RNOH/arkui/LoadingProgressNode.h"
#include "ShadowNodes.h"

namespace rnoh {
    class RNCMaterialHeaderComponentInstance
        : public CppComponentInstance<facebook::react::RNCMaterialHeaderShadowNode>,
          public HeaderNodeDelegate {

    private:
        StackNode m_stackNode;
        ArkUI_NodeHandle imageStack{m_stackNode.getArkUINodeHandle()};
        LoadingProgressNode progressNode;
        float mWindowWidth{0.0};
        bool isRefreshed{false};

    public:
        RNCMaterialHeaderComponentInstance(Context context);
        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    
        StackNode &getLocalRootArkUINode() override;
        void onRefreshStatusChange(int32_t status) override;
        void addHeader(int32_t screenWidth, int32_t index, ArkUINode *arkUI_Node) override;
        void onHeaderMove(float dur) override;
        void setScaleAnimate(int32_t dur);
    };
} // namespace rnoh
