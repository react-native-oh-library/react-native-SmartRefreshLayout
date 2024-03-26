#include "PullToRefreshNode.h"
#include <glog/logging.h>
#include <arkui/native_node.h>
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {
    PullToRefreshNode::PullToRefreshNode()
        : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_COLUMN)),
          m_headerArkUINodeHandle(nullptr), m_listArkUINodeHandle(nullptr), m_pullToRefreshNodeDelegate(nullptr) {
        ArkUI_NumberValue columnFlexValue[] = {{.i32 = ARKUI_FLEX_ALIGNMENT_CENTER}};
        ArkUI_AttributeItem columnFlexItem = {columnFlexValue, sizeof(columnFlexValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_COLUMN_JUSTIFY_CONTENT, &columnFlexItem);
    }

    PullToRefreshNode::~PullToRefreshNode() {
    }
    void PullToRefreshNode::setPullToRefreshNodeDelegate(PullToRefreshNodeDelegate *pullToRefreshNodeDelegate) {
        m_pullToRefreshNodeDelegate = pullToRefreshNodeDelegate;
    }

    void PullToRefreshNode::insertChild(ArkUINode &child, std::size_t index) {
        if (index == 0) {
            m_headerArkUINodeHandle = child.getArkUINodeHandle();
            ArkUI_NumberValue alignments[] = {{.u32 = ARKUI_ALIGNMENT_BOTTOM}};
            ArkUI_AttributeItem alignment = {alignments, sizeof(alignments) / sizeof(ArkUI_NumberValue)};
            NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_STACK_ALIGN_CONTENT, &alignment);
        } else if (index == 1) {
            m_listArkUINodeHandle = child.getArkUINodeHandle();
        }
        maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(), index));
    }

    void PullToRefreshNode::removeChild(ArkUINode &child) {
        maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
        if (m_headerArkUINodeHandle == child.getArkUINodeHandle()) {
            m_headerArkUINodeHandle = nullptr;
        } else {
            m_listArkUINodeHandle = nullptr;
        }
    }

    void PullToRefreshNode::setHeaderHeight(float h) {
        ArkUI_NumberValue heightNumberValue[] = {h};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_HEIGHT, &heightItem);
    }

    void PullToRefreshNode::setEnableRefresh(bool enable) { refreshConfigurator.setHasRefresh(enable); }
    void PullToRefreshNode::setMaxTranslate(float maxHeight) { refreshConfigurator.setMaxTranslate(maxHeight); }
    void PullToRefreshNode::setHeaderBackgroundColor(facebook::react::SharedColor &color) {
        uint32_t colorValue1 = *color;
        ArkUI_NumberValue preparedColorValue1[] = {{.u32 = colorValue1}};
        ArkUI_AttributeItem colorItem1 = {preparedColorValue1, sizeof(preparedColorValue1) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_headerArkUINodeHandle, NODE_BACKGROUND_COLOR, &colorItem1);
    }

} // namespace rnoh