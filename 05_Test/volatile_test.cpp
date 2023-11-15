//
// Created by 86188 on 2023/9/6.
//

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

    std::cout << counter;
    return 0;
}