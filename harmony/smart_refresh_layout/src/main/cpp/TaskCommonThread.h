//
// Created on 2024/4/3.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

//
// Created on 10/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_ANIMATION_H
#define HARMONY_ANIMATION_H
#include <thread>
#include <atomic>
#include <chrono>

class TaskCommonThread {
public:
    TaskCommonThread() {}
    ~TaskCommonThread() { cancelTask(); }

    void setTaskParams(std::chrono::milliseconds durationSeconds, std::function<void(double)> callback) {
        duration_ = durationSeconds;
        callback_ = callback;
        if (!callback_) {
            throw std::invalid_argument("Callback cannot be null");
        }
    }
    void execute() { updateThread_ = new std::thread(&TaskCommonThread::task, this); }

private:
    void task() {
        for (double t = 0.01; t <= 1.0; t += 0.01) {
            callback_(t);
            std::this_thread::sleep_for(duration_ * 0.01);
        }
    }

private:
    std::chrono::milliseconds duration_;
    std::thread *updateThread_;
    std::function<void(double)> callback_;
    void cancelTask() {
        if (updateThread_ != nullptr) {
            updateThread_->join();
            delete updateThread_;
            updateThread_ = nullptr;
        }
    }
};
#endif // HARMONY_ANIMATION_H
