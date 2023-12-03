#include "parallel_scheduler.cpp"
#include <wait.h>
#include <iostream>

void task(int id) {
    std::cout << "task by id - " << id << " executed by thread " << pthread_self() << std::endl;
}

int main() {
    const int capacity = 4;
    parallel_scheduler scheduler(capacity);

    for (int i = 0; i < 10; ++i) {
        scheduler.run([i]() { task(i); });
    }
        sleep(5);
    return 0;
}
