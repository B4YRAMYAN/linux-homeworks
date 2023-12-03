#include "parallel_scheduler.h"

parallel_scheduler::parallel_scheduler(int capacity) : capacity(capacity), stop(false) {
    pthread_mutex_init(&mtx, nullptr);
    pthread_cond_init(&cond, nullptr);
    for (int i = 0; i < capacity; ++i) {
        pthread_t thread;
        pthread_create(&thread, nullptr, worker_thread, this);
        threads.push_back(thread);
    }
}

void parallel_scheduler::execute_task() {
    while (true) {
        pthread_mutex_lock(&mtx);

        while (taskQu.empty() && !stop) {
            pthread_cond_wait(&cond, &mtx);
        }

        if (stop) {
            pthread_mutex_unlock(&mtx);
            break;
        }

        auto curr = taskQu.front();
        taskQu.pop();

        pthread_mutex_unlock(&mtx);

        curr();
    }
}

void* parallel_scheduler::worker_thread(void* arg) {
    auto* scheduler = static_cast<parallel_scheduler*>(arg);
    scheduler->execute_task();
    return nullptr;
}

void parallel_scheduler::run(std::function<void()> func) {
    pthread_mutex_lock(&mtx);
    taskQu.push(func);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx);
}

parallel_scheduler::~parallel_scheduler() {
    stop = true;
    pthread_cond_broadcast(&cond);

    for (auto& td : threads) {
        pthread_join(td, nullptr);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
}
