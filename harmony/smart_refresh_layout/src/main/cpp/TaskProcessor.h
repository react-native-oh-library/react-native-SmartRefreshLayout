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

#include <thread>
#include <atomic>
#include <chrono>

class TaskProcessor {
public:
    TaskProcessor() {}
    ~TaskProcessor() { cancelTask(); }

    void startDelayTask(std::chrono::milliseconds durationSeconds, std::function<void(void)> callback) {
        delayTime = durationSeconds;
        callback_ = callback;
        if (!callback_) {
            throw std::invalid_argument("Callback cannot be null");
        }
        updateThread_ = new std::thread(&TaskProcessor::task, this);
    }

private:
    void task() {
        std::this_thread::sleep_for(delayTime);
        callback_();
    }

private:
    std::chrono::milliseconds delayTime;
    std::thread *updateThread_;
    std::function<void(void)> callback_;
    void cancelTask() {
        if (updateThread_ != nullptr) {
            if (updateThread_->joinable()) {
                updateThread_->join();
            }
            delete updateThread_;
            updateThread_ = nullptr;
        }
    }
};