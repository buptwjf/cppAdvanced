//
// Created by 86188 on 2023/8/2.
//

#include <iostream>
#include <memory>
#include <thread>

/*
 * 强智能指针和弱智能指针
 * ared_ptr  强智能指针  可以改变资源的引用计数
 * weak_ptr 弱智能指针 不会改变资源的引用计数
 * weak_ptr => shared_ptr => 资源内存
 *
 * 强智能指针的循环引用是什么问题？什么结果？怎么解决？
 * */

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


int main() {
    shared_ptr<A> pa(new A());
    shared_ptr<B> pb(new B());
    pa->_ptrb = pb;
    pb->_ptra = pa;

    cout << pa.use_count() << endl;
    cout << pb.use_count() << endl;
    return 0;
}