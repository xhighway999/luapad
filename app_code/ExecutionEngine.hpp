#pragma once

#include <functional>
#include <thread>
#include <memory>
#include <atomic>

class ExecutionEngine
{
public:
    ExecutionEngine();
    void setTask(std::function<void()> task);
    bool isRunning() {return running;}
    void killWorker();
private:
    std::shared_ptr<std::thread> workerThread = nullptr;
    std::atomic<bool> running = false;
    std::function<void()> workerTask;
    //pthread_t tid;
};

