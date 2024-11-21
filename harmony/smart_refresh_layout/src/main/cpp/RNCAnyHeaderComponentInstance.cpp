#include "RNCAnyHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "SmartUtils.h"

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
    double pointScaleFactor = getLayoutMetrics().pointScaleFactor;
    m_stackNode.setLayoutRect({0, 0},
                              {SmartUtils::vp2px(pointScaleFactor, getLayoutMetrics().frame.size.width),
                               SmartUtils::vp2px(pointScaleFactor, childHeight)},
                              1.0);
    }

    void RNCAnyHeaderComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        if (props == nullptr) {
            return;
        }
        backColor = props->primaryColor;
    }

    facebook::react::SharedColor RNCAnyHeaderComponentInstance::GetPrimaryColor() {
        return SmartUtils::parseColor(backColor);
    }

} // namespace rnoh