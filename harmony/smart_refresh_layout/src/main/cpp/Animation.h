//
// Created on 10/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_ANIMATION_H
#define HARMONY_ANIMATION_H
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <glog/logging.h>

typedef enum {
    ANIMATION_FREE = 0,
    ANIMATION_START = 1,
    ANIMATION_RUN = 2,
    ANIMATION_FINISH = 3,
} Animation_State;

class Animation {
public:
    Animation() { state_ = Animation_State::ANIMATION_FREE; }


    ~Animation() { cancelAnimation(); }

    void SetAnimationParams(std::chrono::milliseconds durationSeconds, double startValue, double endValue,
                            std::function<void(double)> callback) {
        duration_ = durationSeconds; //150
        currentValue_ = startValue; //50
        targetValue_ = endValue;   // 0
        startValue_ = startValue;  //50
        callback_ = callback;
        if (!callback_) {
            throw std::invalid_argument("Callback cannot be null");
        }
    }

    void Rest() { cancelAnimation(); }
    double GetCurrentValue() const { return currentValue_; }
    Animation_State GetAnimationStatus() { return state_; }
    void Start() {
        state_ = Animation_State::ANIMATION_START;
        startTime_ = std::chrono::steady_clock::now();
        // 启动更新线程
        updateThread_ = new std::thread(&Animation::UpdateLoop, this);
        //         updateThread_ = new std::thread(&Animation::Animate, this);
    }
    
    void UpdateLoop() {
        state_ = Animation_State::ANIMATION_RUN;
        LOG(INFO) << "[tyBrave] Animation startValue_: " << startValue_ << ";currentValue_:" << currentValue_;
        const double p0 = 0.1, p1 = 0.0, p2 = 0.58, p3 = 1.0; // CubicBezier控制点
        auto startTime = std::chrono::high_resolution_clock::now();
        for (double t = 0.0; t < 1.01; t += 0.01) {
            LOG(INFO) << "[tyBrave1] Animation progress: " << ";t:" << t;
            // 逐步增加t的值来模拟动画进度
            double progress = cubicBezier(t, p0, p1, p2, p3); // 计算CubicBezier曲线上的点作为进度
            currentValue_ = startValue_ + (targetValue_ - startValue_) * progress; // 根据进度计算当前值
            callback_(currentValue_);                                              // 调用回调函数处理当前值
            // 暂停以匹配动画的持续时间
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
            if (elapsed < duration_ * progress) {
                std::this_thread::sleep_for((duration_ * progress - elapsed) * 0.1);
            }
            startTime = currentTime; // 重置开始时间以计算下一帧的延迟
        }
        callback_(targetValue_);
        state_ = Animation_State::ANIMATION_FINISH;
    }

    float Animate() {
        std::chrono::milliseconds stepTime(10); // 每步的时间间隔（毫秒）
        double totalDurationMilliseconds = static_cast<double>(duration_.count());
        for (double elapsedTimeMilliseconds = 0; elapsedTimeMilliseconds < totalDurationMilliseconds;
             elapsedTimeMilliseconds += stepTime.count()) {
            // 计算当前时间比例
            double t = static_cast<double>(elapsedTimeMilliseconds) / totalDurationMilliseconds;

            // 使用CubicBezier计算当前值
            double progress = cubicBezier(t, 0.1, 0.0, 0.58, 1.0);
            currentValue_ = startValue_ + (targetValue_ - startValue_) * progress;
            callback_(currentValue_);
            // 等待一段时间以模拟动画的逐步进行
            std::this_thread::sleep_for(stepTime);
        }
        callback_(targetValue_);
    }


private:
    std::atomic<double> startValue_;
    std::atomic<double> currentValue_;
    double targetValue_;
    Animation_State state_ = Animation_State::ANIMATION_FINISH;
    std::chrono::milliseconds duration_;
    std::chrono::steady_clock::time_point startTime_;
    std::thread *updateThread_; // 使用指针是为了能够动态分配线程对象
    std::function<void(double)> callback_;

    double cubicBezier(double t, double p0, double p1, double p2, double p3) {
        return (1 - t) * p0 + p3 * t;
        //         return pow(1 - t, 3) * p0 + 3 * pow(1 - t, 2) * t * p1 + 3 * (1 - t) * pow(t, 2) * p2 + pow(t, 3) *
        //         p3;
    }
    void cancelAnimation() {
        state_ = Animation_State::ANIMATION_FREE;
        // 等待线程结束
        if (updateThread_ != nullptr) {
            updateThread_->join();
            delete updateThread_; // 如果使用new分配，则需要delete释放
            updateThread_ = nullptr;
        }
    }
};
#endif // HARMONY_ANIMATION_H
