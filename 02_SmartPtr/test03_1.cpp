//
// Created by 86188 on 2023/8/2.
//

#include <iostream>
#include <memory>
#include <thread>

// 智能指针的交叉引用问题
using namespace std;


class B;

class A {
public:
    A() { cout << "A()" << endl; }

    ~A() { cout << "~A()" << endl; };

    void testA() {
        cout << "good way" << endl;
    }

    shared_ptr<B> _ptrb;
};

class B {
public:
    B() { cout << "B()" << endl; }

    ~B() { cout << "~B()" << endl; };

    shared_ptr<A> _ptra;
};

// 子线程
void handler01(weak_ptr<A> pw) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // q 访问A对象的时候，需要侦测A对象是否存活
    shared_ptr<A> sp = pw.lock();
    if(sp!= nullptr){
        sp->testA();
    }
    else{
        cout << "~A is over" << endl;
    }
}

// main 线程
int main() {
    {
        shared_ptr<A> p(new A());
        thread t1(handler01, weak_ptr<A>(p));
        t1.detach();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        // 这样修改
    }

    // 把子线程
    cout << "over!!!" << endl;
    return 0;
}