//
// Created by 86188 on 2023/8/2.
//
#include "iostream"
#include "memory"

using namespace std;

template<typename T>
class CSmartPtr {
public:
    explicit CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}

    ~CSmartPtr() {
        cout << "~CSmartPtr" << endl;
        delete mptr;
        mptr = nullptr;
    }

    // 定义自己的拷贝构造函数，但是不能实现浅拷贝
//    CSmartPtr(const CSmartPtr<T> &src) {
//        mptr = new T(*src.mptr);
//    }
    CSmartPtr(const CSmartPtr<T> &src) {
        mptr = src.mptr;
    }

    T &operator*() { return *mptr; }

    T *operator->() { return mptr; }

private:
    T *mptr;
};

class Test {
public:
    Test() {
        cout << "Test()" << endl;
    }

    void static test() {
        cout << "use test" << endl;
    }
};

int main() {
    CSmartPtr<int> p1(new int);
//    CSmartPtr<int> p2(p1); // 报错：因为是浅拷贝
    // p1 p2 指向不同的内存，不是用户想要的结果（指向同一片内存）

    auto_ptr<int> ptr1(new int);
    auto_ptr<int> ptr2(ptr1);

    *ptr2 = 20;
    cout << *ptr2 << endl;

//    scoped_ptr<int> ptr3(new int); // 不知道为什么找不到头文件，可能是配置C++11的原因

    unique_ptr<int> ptr4(new int(15));
    unique_ptr<int> ptr5 = move(ptr4);
    cout << "*ptr5 = " << *ptr5 << endl;
    unique_ptr<int> ptr6(new int(25));
    ptr5 = move(ptr6);
    cout << "*ptr5 = " << *ptr5 << endl;
    return 0;
}