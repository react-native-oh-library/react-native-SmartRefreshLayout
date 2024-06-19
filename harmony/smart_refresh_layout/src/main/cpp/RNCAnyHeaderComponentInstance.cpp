#include "RNCAnyHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

    RNCAnyHeaderComponentInstance::RNCAnyHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        ArkUI_NumberValue clipValue[] = {{.u32 = 1}};
        ArkUI_AttributeItem clipItem = {clipValue, sizeof(clipValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_stackNode.getArkUINodeHandle(), NODE_CLIP, &clipItem);
        }

    void RNCAnyHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                        std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCAnyHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    SmartStackNode &RNCAnyHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void RNCAnyHeaderComponentInstance::finalizeUpdates() {
        std::vector<ComponentInstance::Shared> child = getChildren();
        float childHeight = 0.0;
        for (ComponentInstance::Shared c : child) {
            if (c) {
               auto height = c->getLayoutMetrics().frame.size.height;
               if (height>childHeight) {
                  childHeight = height;
               }
             }
        }
        auto rnInstancePtr = this->m_deps->rnInstance.lock();
        if (rnInstancePtr != nullptr) {
            auto turboModule = rnInstancePtr->getTurboModule("RNCSmartRefreshContext");
            auto arkTsTurboModule = std::dynamic_pointer_cast<rnoh::ArkTSTurboModule>(turboModule);
            folly::dynamic result = arkTsTurboModule->callSync("cvp2px", {getLayoutMetrics().frame.size.width});;
            folly::dynamic result1 = arkTsTurboModule->callSync("cvp2px", {childHeight});
            m_stackNode.setLayoutRect({0, 0}, {result["values"].asDouble(), result1["values"].asDouble()}, 1.0);
        }
    }

} // namespace rnoh