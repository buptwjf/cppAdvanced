//
// Created by 86188 on 2023/8/24.
//
#include <iostream>
#include <list>
#include <thread>
#include <mutex>
/*
 * 模拟车站三个窗口买票的程序
 * */

using namespace std;
int ticketCount = 100; // 有 100 张车票，三个窗口一起卖票
mutex mtx; // 一把全局的互斥锁

/*
 * 多线程程序
 * 竞态条件：多线程程序执行的结果是一致的，不会催着CPU对线程不同的调用顺序，而产生不同的运行结果
 * 线程间互斥 => 互斥锁 mutex => lock_guard 封装 mutex，出作用域 lock_guard 就会自动释放 mutex
 * */
// 模拟卖票的线程函数
void sellTicket(int index) {
    while (ticketCount >= 1) {
        mtx.lock();  // 加锁
        if (ticketCount >= 1) { // 双重判定
            // 临界区代码段 => 原子操作 => 线程间互斥操作 => mutex
            cout << "Window: " << index << " sells  No." << ticketCount << "ticket" << endl;
            ticketCount--;
        }
        mtx.unlock();  // 解锁
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    // 当线程一 变为 0 后，线程二又进来了
}

void sellTicket1(int index) {
    while (ticketCount >= 1) {
        {
            // 使用智能指针加锁 这样不用 加锁和解锁
//            lock_guard<mutex> lock(mtx);  // 加锁 类似于 scoped_ptr 建议用这个
            unique_lock<mutex> lock(mtx);  // 类似 unique_ptr
//            lock.lock() // 不用 lock
            if (ticketCount >= 1) { // 双重判定
                // 临界区代码段 => 原子操作 => 线程间互斥操作 => mutex
                cout << "Window: " << index << " sells  No." << ticketCount << "ticket" << endl;
                ticketCount--;
            }
//            lock.unlock();
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
// 当线程一 变为 0 后，线程二又进来了

int main() {
    // 定义三个线程模拟窗口卖票
    list<thread> tlist;
    for (int i = 1; i <= 3; i++) {
        tlist.emplace_back(sellTicket1, i);
    }
    for (auto &t: tlist) {
        t.join();
    }
    cout << "All windows over!" << endl;
    return 0;
}