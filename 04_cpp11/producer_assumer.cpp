//
// Created by 86188 on 2023/8/25.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <queue> // C++ STL 所有的容器都不是线程安全的
#include <condition_variable>

using namespace std;

/*
 * C++多线程编程的问题
 * 1. 线程间的互斥
 *      多线程代码在运行的时候，存在竞态条件，多线程程序运行结果应该是一样的
 *      竞态条件 => 临界区代码段 => 原子操作 => 线程互斥锁 mutex 轻量级的无锁实现 CAS
 *      strace ./a.out mutex => pthread_mutex_t
 * 2. 线程间的同步通信
 *      生产者-消费者线程模型
 * */

mutex mtx;
condition_variable cv; // 定义条件变量，做线程间的通信

class Queue {
public:
    void put(int val) {
        // 使用 lock_guard
//        lock_guard<mutex> lck(mtx); // 类似 scoped_ptr
        unique_lock<mutex> lck(mtx); // 类似 unique_ptr
        while (!que.empty()) {
            // que 不为空，应该通知消费者消费完了再去生产
            // 1. 生产者线程进入等待状态，2.并且把 mtx 互斥锁释放掉
            cv.wait(lck);
        }
        que.push(val);

        /*
         * notify_one
         * notify_all
         * */
        // 通知其他线程，我生产了一个物品，你们赶紧消费吧
        // 其他线程得到该通知，就会从等待状态 => 阻塞状态 => 获取互斥锁才能继续进行
        cv.notify_all();
        cout << "producer No." << val << " product." << endl;
    }

    int get() {
        unique_lock<mutex> lck(mtx);
        while (que.empty()) {
            // 消费者线程发现 que 是空的，通知生产者线程先生产物品
            // #1 进入等待状态 # 把互斥锁 mutex 释放
            cv.wait(lck);
        }
        int val = que.front();
        que.pop();
        cv.notify_all(); // 通知生产者线程，我消费完成了
        cout << "consumer No." << val << " product." << endl;
        return val;
    }

private:
    queue<int> que;
};

void producer(Queue *que) {
    for (int i = 0; i < 10; ++i) {
        que->put(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

}

void consumer(Queue *que) {
    for (int i = 0; i < 10; ++i) {
        que->get();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    Queue que;
    thread t1(producer, &que);
    thread t2(consumer, &que);
    t1.join();
    t2.join();
    return 0;
}