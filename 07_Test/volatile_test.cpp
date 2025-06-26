//
// Created by 86188 on 2023/9/6.
//
// volatile
// 它防止的是编译器优化，不是线程之间的竞态条件。
// 它不会加锁，也不会使读写操作变成原子操作。
#include <pthread.h>
#include <atomic>
#include <iostream>
volatile int counter = 0;

void *increment(void *arg) {
    for (int i = 0; i < 100000; i++) {
         counter++;
    }
    return nullptr;
}

int main() {
    pthread_t thread1, thread2;

    // 创建两个线程，分别执行increment函数
    pthread_create(&thread1, nullptr, increment, nullptr);
    pthread_create(&thread2, nullptr, increment, nullptr);
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    std::cout << counter; // 由于两个产生竞态，因此结果不唯一 可能为 20000 可能为 10000多
    return 0;
}