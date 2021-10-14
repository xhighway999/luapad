#include "ExecutionEngine.hpp"
#include <pthread.h>
#include <signal.h>
#include <thread>
#include <iostream>

ExecutionEngine::ExecutionEngine()
{
     auto ta = [ this](){



        while (true) {
            if (running) {
                try {
                    std::cout << "running task now" << std::endl;
                    workerTask();

                }  catch (...) {
                    std::cout << "Unknown error" << std::endl;
                }
                running = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    };

     workerThread = std::make_shared<std::thread>(ta);
}

void ExecutionEngine::setTask(std::function<void ()> task)
{
    //signal(SIGUSR1, handler);
    killWorker();

    workerTask = task;
    running = true;

}

void ExecutionEngine::killWorker()
{


    while (running) {
     std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}
