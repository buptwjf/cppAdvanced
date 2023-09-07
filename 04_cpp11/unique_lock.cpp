//
// Created by 86188 on 2023/8/25.
//

#include <mutex>
#include <condition_variable>

using namespace std;
/*
 * 1. lock_guard 和 unique_lock
 * 2. condition_variable wait 和 notify_all
 * */

mutex mtx;
condition_variable cv;

int main() {
    /*
     * 通知在 cv 上等待的线程，条件成立了，起来干活了!
     * 其他在 cv 上等待的线程，收到通知，从等待状态 => 阻塞状态 => 获取互斥锁 => 线程继续运行
     * */
    cv.notify_all();

    // 实现在构造函数和析构函数种进行 lock 和 unlock
    // 不可能用在函数参数传递或者返回过程种，因为他没有拷贝构造和赋值，
    // 只能用于在简单的临界区代码段的互斥操作中,不能用于参数传递和返回值
    lock_guard<mutex> guard(mtx);
    // 可以用在函数调用的过程中
    unique_lock<mutex> lck(mtx);

    // #1. 使线程进入等待状态
    // #2. lock.unlock 可以把 mtx 给释放掉
    cv.wait(lck);

    return 0;
}