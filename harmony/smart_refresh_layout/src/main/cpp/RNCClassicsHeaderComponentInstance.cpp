//
// Created on 2024/3/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNCClassicsHeaderComponentInstance.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "react/renderer/imagemanager/primitives.h"
#include "SmartRefreshState.h"

namespace rnoh {

    RNCClassicsHeaderComponentInstance::RNCClassicsHeaderComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        LOG(INFO) << "[tyBrave] <RNCClassicsHeaderComponentInstance {}";

        mColumnHandle = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_ROW);

        facebook::react::ImageSources imageSources;
        imageSources.push_back({.uri = "resource://BASE/media/icon_up.png"});
        imageNode.setSources(imageSources);
        imageNode.setSize({30, 20});
        imageNode.setResizeMode(facebook::react::ImageResizeMode::Contain);

        facebook::react::ImageSources imageUpdateSources;
        imageUpdateSources.push_back({.uri = "resource://BASE/media/icon_load.png"});
        updateImageNode.setSources(imageUpdateSources);
        updateImageNode.setSize({25, 25});
        updateImageNode.setResizeMode(facebook::react::ImageResizeMode::Contain);


        auto textColumn = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_COLUMN);

        ArkUI_NumberValue margin_self[] = {{.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 12}};
        ArkUI_AttributeItem margin[] = {margin_self, 4};
        NativeNodeApi::getInstance()->setAttribute(textColumn, NODE_MARGIN, margin);

        textNode.setTextContent("下拉刷新");
        textNode.setFontSize(15);
        textNode.setFontColor(0xff666666);

        timeTextNode.setTextContent("更新于 早上10:10");
        timeTextNode.setFontSize(12);
        timeTextNode.setFontColor(0xff7c7c7c);


        NativeNodeApi::getInstance()->insertChildAt(textColumn, textNode.getArkUINodeHandle(), 0);
        NativeNodeApi::getInstance()->insertChildAt(textColumn, timeTextNode.getArkUINodeHandle(), 1);

        std::time_t now_seconds = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm *now_tm = std::localtime(&now_seconds);

        LOG(INFO) << "[tyBrave] <RNCClassicsHeaderComponentInstance {}"
                  << "当前时间: " << (now_tm->tm_year + 1900) << '-' << (now_tm->tm_mon + 1) << '-' << now_tm->tm_mday
                  << ' ' << now_tm->tm_hour << ':' << now_tm->tm_min << ':' << now_tm->tm_sec;


        mColumnHandle = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_ROW);

        ArkUI_NumberValue heightNumberValue[] = {50};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(mColumnHandle, NODE_HEIGHT, &heightItem);

        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, imageNode.getArkUINodeHandle(), 0);
        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, updateImageNode.getArkUINodeHandle(), 1);
        NativeNodeApi::getInstance()->insertChildAt(mColumnHandle, textColumn, 2);
        NativeNodeApi::getInstance()->insertChildAt(m_stackNode.getArkUINodeHandle(), mColumnHandle, 0);

        //         ArkUI_NumberValue positionArray[] = {{.f32 = -50}, {.f32 = 20}};
        //         ArkUI_AttributeItem positionValue[] = {positionArray, 2};
        //         NativeNodeApi::getInstance()->setAttribute(timeTextNode.getArkUINodeHandle(), NODE_POSITION,
        //         positionValue);
    }
    void RNCClassicsHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                             std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void RNCClassicsHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &RNCClassicsHeaderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void RNCClassicsHeaderComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        if (props != nullptr) {
            //             facebook::react::SharedColor headerColor = props->primaryColor;
            //             LOG(INFO) << "[tyBrave] <SmartRefreshLayoutComponentInstance ---------------" <<
            //             props->accentColor
            //                       << ";sss:" << props->primaryColor;
            //             if (props->accentColor) {
            //                 textNode.setFontColor(props->accentColor);
            //                 imageNode.setTintColor(props->accentColor);
            //             }
        }
    }

    void RNCClassicsHeaderComponentInstance::finalizeUpdates() {
        ArkUI_NumberValue heightNumberValue[] = {60};
        ArkUI_AttributeItem heightItem = {heightNumberValue, 1};
        NativeNodeApi::getInstance()->setAttribute(m_stackNode.getArkUINodeHandle(), NODE_HEIGHT, &heightItem);
        m_stackNode.setAlignment(ARKUI_ALIGNMENT_BOTTOM);
    }

    void RNCClassicsHeaderComponentInstance::setImageRotate(float angle) {
        ArkUI_NumberValue opacityValue[] = {{.f32 = 0}, {.f32 = 0}, {.f32 = 1}, {.f32 = angle}, {.f32 = 0}};
        ArkUI_AttributeItem opacityItem = {opacityValue, sizeof(opacityValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_ROTATE, &opacityItem);
    }

    void RNCClassicsHeaderComponentInstance::onRefreshStatusChange(int32_t status) {

        ArkUI_NumberValue imageNodeVisiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_VISIBLE}};
        ArkUI_AttributeItem imageNodeVisiblyAbleItem = {imageNodeVisiblyAbleValue, 1};
        NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                   &imageNodeVisiblyAbleItem);
        switch (status) {
        case IS_FREE:
        case IS_PULL_DOWN_1: {
            textNode.setTextContent("下拉刷新");
            setImageRotate(180.0);
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(updateImageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        case IS_REFRESHING: {
            textNode.setTextContent("正在更新");
            ArkUI_NumberValue imageNodeVisiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem imageNodeVisiblyAbleItem = {imageNodeVisiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(imageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &imageNodeVisiblyAbleItem);

            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_VISIBLE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(updateImageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        }

        break;
        case IS_PULL_DOWN_2: {
            textNode.setTextContent("释放刷新");
            setImageRotate(0.0);
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(updateImageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        case IS_REFRESHED: {
            textNode.setTextContent("刷新完毕");
            ArkUI_NumberValue visiblyAbleValue[] = {{.u32 = ARKUI_VISIBILITY_NONE}};
            ArkUI_AttributeItem visiblyAbleItem = {visiblyAbleValue, 1};
            NativeNodeApi::getInstance()->setAttribute(updateImageNode.getArkUINodeHandle(), NODE_VISIBILITY,
                                                       &visiblyAbleItem);
        } break;
        }
    }
} // namespace rnoh