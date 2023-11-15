//
// Created by 86188 on 2023/8/2.
//

#include <iostream>

using namespace std;

// 利用栈上的对象出作用域自动析构的特点，保证资源的自动释放
// 智能指针只能作用栈区，不能作用在堆区

/*
 * 如何实现一个最简单的智能指针
 * 1. 构造函数
 * 2. 析构函数
 * 3. * 运算符重载
 * 4. -> 运算符重载
 * */


template<typename T>
class CSmartPtr {
public:
    // 构造
    explicit CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}

    // 使用 explicit 可以保证只能使用显示的参数，不会参数隐式变换
    // 析构
    ~CSmartPtr() { delete mptr; }

    // 实现 * 解引用功能
    T &operator*() { return *mptr; } // 这里必须有 &
    // 实现 -> 功能
    T *operator->() { return mptr; }

private:
    T *mptr;
};

class Test {
public:
    Test() {
        cout << "Test()" << endl;
    }

    // 保证不会访问或修改任何(非)对象数据成员
    void static test() {
        cout << "use test" << endl;
    }
};

int main() {
    CSmartPtr<int> ptr1(new int);
    *ptr1 = 20;
//    cout << *ptr1 << endl;

    CSmartPtr<Test> ptr2(new Test());
    // ptr.operator->()->test();
    ptr2->test();

    return 0;
}