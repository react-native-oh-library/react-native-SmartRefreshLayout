//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCStoreHouseHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "SmartUtils.h"

namespace rnoh {

RNCStoreHouseHeaderComponentInstance::RNCStoreHouseHeaderComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
    m_storeHouseNode.setStoreHouseNodeDelegate(this);
}

void RNCStoreHouseHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                           std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
}

void RNCStoreHouseHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
    CppComponentInstance::onChildRemoved(childComponentInstance);
};

float RNCStoreHouseHeaderComponentInstance::getVp2Px(float v) {
    return SmartUtils::vp2px(getLayoutMetrics().pointScaleFactor, v);;
}
facebook::react::SharedColor RNCStoreHouseHeaderComponentInstance::GetPrimaryColor() { return -1; };
void RNCStoreHouseHeaderComponentInstance::onHeaderMove(float dur) { m_storeHouseNode.setProgress(dur); };
void RNCStoreHouseHeaderComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    if (props != nullptr) {
        m_storeHouseNode.setDropHeight(props->dropHeight);
        m_storeHouseNode.setFontSize(props->fontSize);
        m_storeHouseNode.setLineWidth(props->lineWidth);
        m_storeHouseNode.setTextColor(props->textColor);
        if (!props->text.empty()) {
            m_storeHouseNode.setText(props->text);
        }
    }
    m_storeHouseNode.initStoreHouse();
}
RNCStoreHouseHeaderNode &RNCStoreHouseHeaderComponentInstance::getLocalRootArkUINode() { return m_storeHouseNode; }

} // namespace rnoh