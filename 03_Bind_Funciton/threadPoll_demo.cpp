//
// Created by 86188 on 2023/8/17.
//
#include <iostream>
#include <functional>
#include <thread>

using namespace std;

/*
    模拟 muduo 库的线程和线程池
*/

// 线程类
class Thread {
public:
    Thread(function<void(int)> func, int no) : _func(func), _no(no) {}

    thread start() {
        thread t(_func, _no); // _func()
        return t;
    }

private:
    function<void(int)> _func;
    int _no;

};

// 线程池类
class ThreadPool {
public:
    ThreadPool() {}

    ~ThreadPool() {
        // 释放 Thread 对象占用的堆资源
        for (int i = 0; i < _pool.size(); ++i) {
            delete _pool[i];
            cout << "~ThreadPoll " << i << endl;
        }
    }

    // 开启线程池
    void startPool(int size) {
        for (int i = 0; i < size; i++) {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, placeholders::_1), i));
        }

        for (int i = 0; i < size; ++i) {
            _handler.push_back(_pool[i]->start());
        }

        for (thread &t: _handler) {
            t.join();
        }
    }

private:
    vector<Thread *> _pool;
    vector<thread> _handler;

    // 把 runInThread 这个方法充当线程函数
    // C++ thread   C pthread_create 需要的都是 C 函数，不能用成员方法 但可以用绑定器做到
    void runInThread(int id) {
        cout << "call runInThread!" << id << endl;
    }
};

int main() {
    ThreadPool pool;
    pool.startPool(10);
    return 0;
}