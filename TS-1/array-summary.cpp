#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <pthread.h>
#include <chrono>

struct ThreadInfo {
    int threadIndex;                           // index of the current thread
    const std::vector<int>* arr;               // use pointers instead of references
    int numThreads;                            // total number of threads
    std::vector<long long int>* partialSums;   // use pointers instead of references
};

long long int calculateSum(const std::vector<int>& arr) {
    long long int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return sum;
}

void* threadFunction(void* arg) {
    ThreadInfo* info = static_cast<ThreadInfo*>(arg);

    // calculate the start and end indices for the portion of the array to be processed by the current thread
    std::size_t start = (info->arr->size() / info->numThreads) * info->threadIndex;
    std::size_t end = (info->threadIndex == info->numThreads - 1) ? info->arr->size() : start + (info->arr->size() / info->numThreads);

    // calculate the partial sum for the assigned portion of the array
    for (std::size_t i = start; i < end; ++i) {
        (*info->partialSums)[info->threadIndex] += (*info->arr)[i];
    }

    pthread_exit(nullptr);
}

long long int calculateSumWithThreads(const std::vector<int>& arr, const int numThreads) {
    pthread_t threads[numThreads];
    std::vector<long long int> partialSums(numThreads, 0);
    ThreadInfo threadInfo[numThreads];

    // Create and launch threads
    for (int i = 0; i < numThreads; ++i) {
        // prepare information to be passed to each thread
        threadInfo[i] = {i, &arr, numThreads, &partialSums};

        // create a thread and execute the threadFunction
        int result = pthread_create(&threads[i], nullptr, threadFunction, &threadInfo[i]);
        if (result != 0) {
            std::cerr << "Error thread was not created " << result << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // wait for threads to finish
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // calculate the total sum from partial sums
    long long int totalSum = 0;
    for (long long int partialSum : partialSums) {
        totalSum += partialSum;
    }

    return totalSum;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "argc is not valid" << std::endl;
        exit(1);
    }

    // parse command line arguments
    int arraySize = std::atoi(argv[1]);
    int numThreads = std::atoi(argv[2]);

    // initialize array with random values
    std::vector<int> arr(arraySize);
    std::srand(std::time(0));
    for (int& value : arr) {
        value = std::rand();
    }

    // calculate sum without threads and measure time
    auto startWithoutThreads = std::chrono::high_resolution_clock::now();
    long long int sumWithoutThreads = calculateSum(arr);
    auto endWithoutThreads = std::chrono::high_resolution_clock::now();
    auto durationWithoutThreads = std::chrono::duration_cast<std::chrono::microseconds>(endWithoutThreads - startWithoutThreads).count();

    // calculate sum with threads and measure time
    auto startWithThreads = std::chrono::high_resolution_clock::now();
    long long int sumWithThreads = calculateSumWithThreads(arr, numThreads);
    auto endWithThreads = std::chrono::high_resolution_clock::now();
    auto durationWithThreads = std::chrono::duration_cast<std::chrono::microseconds>(endWithThreads - startWithThreads).count();

    // print results
    std::cout << "Time spent without threads " << durationWithoutThreads << " miliseconds" << std::endl;
    std::cout << "Time spent with " << numThreads << " threads " << durationWithThreads << " miliseconds" << std::endl;
}

