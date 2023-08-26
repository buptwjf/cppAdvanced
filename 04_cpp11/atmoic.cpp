//
// Created by 86188 on 2023/8/25.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <queue> // C++ STL 所有的容器都不是线程安全的
#include <condition_variable>
#include <atomic>
#include <list>

using namespace std;

/*
 * C++ 窗口卖票 int count = 100
 * lock_guard<mutex> guard(mtx)
 * count ++
 * count --
 *
 * 互斥锁比较重，临界区代码做的事情稍稍负责，才划得来用
 * 系统理论：
 * CAS 来保证上面 ++ -- 操作的原子特性就足够了，实现无锁操作
 *      exchange/swap 无锁队列 => CAS 来实现的
 * */

// volitaile 防止多线程程序对共享变量的缓存，都是访问的原始数据
volatile atomic_bool isReady = false;
volatile atomic_int count = 0;

void task() {
    while (!isReady) {
        this_thread::yield(); // 线程出让当前的 CPU 时间片，等待CPU的下一次调度
    }
    for (int i = 0; i < 100; ++i) {
        count++;
    }
}

int main() {
    list<thread> tlist;
    for (int i = 0; i < 10; ++i) {
        tlist.push_back(thread(task));
    }

    // 主线程睡眠
    this_thread::sleep_for(chrono::seconds(3));
    isReady = true;
    for (auto &t: tlist) {
        t.join();
    }
    cout << "count:" << count << endl;
    return 0;
}