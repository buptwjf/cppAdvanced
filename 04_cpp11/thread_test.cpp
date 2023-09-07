//
// Created by 86188 on 2023/8/24.
//

#include <thread>
#include <iostream>

using namespace std;

/*
 * thread/mutex/conditon_variable
 * lock_quard/unique_lock
 * atomic 基于 CAS 操作的原子类型
 * sleep_for
 *
 * C++语言层面 thread(只是在语言层面加了一个封装)
 * Windows - createThread
 * Linux   - pthread_create
 *
 * 线程内容：
 * 1. 怎么创建启动一个线程
 * std::thread 传入一个线程函数和参数，线程直接开始运行
 * 2. 主线程和子线程的关系
 *      主线程结束前，子线程必须结束
 *      子线程运行完毕，子线程就中止
 * 3. 主线程如何处理子线程
 *      t1.join():主线程等待子线程，当前线程继续往下
 *      t1.detach(): 把t 设置为分离线程，主线程结束，整个进程结束，所有子线程都自动结束
 *      // 类似于守护线程
 * */

void threadHandle1(int time) {
    // 获取子线程的 id 号
    cout << "thread: " << this_thread::get_id() << endl;
    // 让子线程睡眠 2 s
    this_thread::sleep_for(chrono::seconds(time));
    cout << "hello thread1!" << endl;
}

int main() {
    // 创建一个新线程对象，传入一个线程函数，新线程就开始运行了
    thread t1(threadHandle1, 3);
    thread t2(threadHandle1, 6);
    // 主线程等待子线程结束，主线程往下运行
//    t1.join();
//    t2.join();
// 将子线程设置为分离线程
// 否则主线程运行完成，如果主线程发现还有未完成的子线程，主线程就会异常终止
    t1.detach();
    t2.detach();
    cout << "main thread down" << endl;
    return 0;
}