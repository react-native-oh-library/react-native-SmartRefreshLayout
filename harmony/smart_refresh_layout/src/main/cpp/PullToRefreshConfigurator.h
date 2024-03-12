//
// Created on 2024/3/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_PULLTOREFRESHCONFIGURATOR_H
#define HARMONY_PULLTOREFRESHCONFIGURATOR_H

#include "boost/cstdint.hpp"
#include "react/renderer/graphics/Color.h"
#include "react/renderer/graphics/Float.h"
#include <string>
namespace rnoh {
    class PullToRefreshConfigurator {
    private:
        bool hasRefresh = true;                   // 是否具有下拉刷新功能
        bool hasLoadMore = true;                  // 是否具有上拉加载功能
        uint32_t maxTranslate = 100;              // 可下拉上拉的最大距离
        facebook::react::Float sensitivity = 0.7; // 下拉上拉灵敏度
        bool listIsPlacement = true;              // 滑动结束后列表是否归位


        uint32_t animDuration = 150; // 滑动结束后，回弹动画执行时间

        uint32_t refreshHeight = 30; // 下拉动画高度

        facebook::react::SharedColor refreshColor = 0xFF6495ED; // 下拉动画颜色

        facebook::react::SharedColor refreshBackgroundColor = 0xFF64811D; // 下拉动画区域背景色
        //
        //         refreshTextColor ?: ResourceColor = '#999999'; // 下拉加载完毕后提示文本的字体颜色
        //
        //         refreshTextSize ?: number | string | Resource = 18; // 下拉加载完毕后提示文本的字体大小

        uint32_t refreshAnimDuration = 1000; // 下拉动画执行一次的时间
        uint32_t loadImgHeight = 30;         // 上拉图片高度

        std::string loadTextPullUp1 = "正在上拉刷新..."; // 上拉1阶段文本

        std::string loadTextPullUp2 = "放开刷新"; // 上拉2阶段文本

        std::string loadTextLoading = "正在玩命加载中..."; // 上拉加载更多中时的文本

        uint32_t finishDelay = 500; // 刷新完成时，延迟回弹的时间

    public:
        PullToRefreshConfigurator setHasRefresh(const bool hasRefresh) {
            this->hasRefresh = hasRefresh;
            return *this;
        }
        bool getHasRefresh() { return this->hasRefresh; }
        PullToRefreshConfigurator setHasLoadMore(const bool hasLoadMore) {
            this->hasLoadMore = hasLoadMore;
            return *this;
        }
        bool getHasLoadMore() { return this->hasLoadMore; }
        PullToRefreshConfigurator setMaxTranslate(const float maxTranslate) {
            this->maxTranslate = maxTranslate;
            return *this;
        }
        uint32_t getMaxTranslate() { return this->maxTranslate; }
        PullToRefreshConfigurator setSensitivity(const float sensitivity) {
            this->sensitivity = sensitivity;
            return *this;
        }
        facebook::react::Float getSensitivity() { return this->sensitivity; }
        PullToRefreshConfigurator setListIsPlacement(const bool listIsPlacement) {
            this->listIsPlacement = listIsPlacement;
            return *this;
        }
        bool getListIsPlacement() { return this->listIsPlacement; }
        PullToRefreshConfigurator setAnimDuration(const uint32_t animDuration) {
            this->animDuration = animDuration;
            return *this;
        }
        uint32_t getAnimDuration() { return this->animDuration; }
        float getRefreshWidth() {
            if (this->refreshHeight == 0) {
                return this->refreshHeight / 3 * 4;
            }
            return 0.0;
        }
        PullToRefreshConfigurator setRefreshHeight(const uint32_t refreshHeight) {
            this->refreshHeight = refreshHeight;
            return *this;
        }
        uint32_t getRefreshHeight() { return this->refreshHeight; }
        PullToRefreshConfigurator setRefreshColor(const facebook::react::SharedColor refreshColor) {
            this->refreshColor = refreshColor;
            return *this;
        }
        std::string getRefreshColor() { this->refreshColor; }
        PullToRefreshConfigurator setRefreshBackgroundColor(facebook::react::SharedColor refreshBackgroundColor) {
            this->refreshBackgroundColor = refreshBackgroundColor;
        }
        facebook::react::SharedColor getRefreshBackgroundColor() { return this->refreshBackgroundColor; }
        //         PullToRefreshConfigurator setRefreshTextColor(bool listIsPlacement);
        //         bool getRefreshTextColor();
        //         PullToRefreshConfigurator setRefreshTextSize(bool listIsPlacement);
        //         bool getRefreshTextSize();
        //         PullToRefreshConfigurator setLoadBackgroundColor(bool listIsPlacement);
        //         bool getLoadBackgroundColor();
        //         PullToRefreshConfigurator setLoadTextColor(bool listIsPlacement);
        //         bool getLoadTextColor();
        //         PullToRefreshConfigurator setLoadTextSize(bool listIsPlacement);
        //         bool getLoadTextSize();
        PullToRefreshConfigurator setRefreshAnimDuration(const uint32_t refreshAnimDuration) {
            this->refreshAnimDuration = refreshAnimDuration;
            return *this;
        }
        uint32_t getRefreshAnimDuration() { return this->refreshAnimDuration; }
        PullToRefreshConfigurator setLoadImgHeight(const float loadImgHeight) {
            this->loadImgHeight = loadImgHeight;
            return *this;
        }
        float getLoadImgHeight() { return this->loadImgHeight; }
        PullToRefreshConfigurator setLoadTextPullUp1(const std::string loadTextPullUp1) {
            this->loadTextPullUp1 = loadTextPullUp1;
            return *this;
        }
        std::string getLoadTextPullUp1() { return this->loadTextPullUp1; }
        PullToRefreshConfigurator setLoadTextPullUp2(const std::string loadTextPullUp2) {
            this->loadTextPullUp2 = loadTextPullUp2;
            return *this;
        }
        std::string getLoadTextPullUp2() { return this->loadTextPullUp2; }
        PullToRefreshConfigurator setLoadTextLoading(const std::string loadTextLoading) {
            this->loadTextLoading = loadTextLoading;
            return *this;
        }
        std::string getLoadTextLoading() { return this->loadTextLoading; }
        PullToRefreshConfigurator setFinishDelay(const uint32_t finishDelay) {
            this->finishDelay = finishDelay;
            return *this;
        }
        uint32_t getFinishDelay() { return this->finishDelay; }
    };
} // namespace rnoh

#endif // HARMONY_PULLTOREFRESHCONFIGURATOR_H
