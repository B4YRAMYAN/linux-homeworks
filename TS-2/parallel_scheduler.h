#pragma once

#include <vector>
#include <queue>
#include <pthread.h>
#include <functional>

class parallel_scheduler {
    std::size_t capacity;
    std::vector<pthread_t> threads;
    std::queue<std::function<void()>> taskQu;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    bool stop;
    void execute_task();
    static void* worker_thread(void* arg);

  public:
    parallel_scheduler(int capacity);
    void run(std::function<void()> func);
    ~parallel_scheduler();
};