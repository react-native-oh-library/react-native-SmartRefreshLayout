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

    StackNode &RNCAnyHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

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
        m_stackNode.setSize(facebook::react::Size({ getLayoutMetrics().frame.size.width, childHeight}));
    }

} // namespace rnoh