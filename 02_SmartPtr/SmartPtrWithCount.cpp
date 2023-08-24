//
// Created by 86188 on 2023/8/8.
//
/*
 * 带有计数功能的智能指针
 * 1. 负责计数的对象
 *      1.1 资源的计数个数
 *      1.2 指向资源的指针
 * 2. 负责实现智能指针的对象
 *      2.1 指向资源的指针
 *      2.2 指向 RefCnt 的指针
 * */
#include "iostream"

using namespace std;

template<typename T>
class RefCnt {
public:
    // 构造函数
    RefCnt(T *ptr = nullptr) : mptr(ptr) {
        if (mptr != nullptr) {
            mcount = 1;
        }
    }

    // 增加引用次数
    void addRef() { mcount++; }

    int delRef() {
        return --mcount;
    }

private:
    T *mptr;
    int mcount;
};


template<typename T>
class CSmartPtr {
public:
    CSmartPtr(T *ptr = nullptr) : mptr(ptr) {
        myRefCnt = new RefCnt<T>(mptr);
    }

    // 析构函数也要改
    ~CSmartPtr() {
        cout << "~CSmartPtr" << endl;
        // 需要判断自身析构后引用次数是否为 0
        if (0 == myRefCnt->delRef()) {
            delete mptr;
            mptr = nullptr;
        }
    }

    // 关键：重写拷贝构造
    CSmartPtr(const CSmartPtr<T> &src)
            : mptr(src.mptr), myRefCnt(src.myRefCnt) {
        if (mptr != nullptr) {
            myRefCnt->addRef();
        }
    }

    T &operator*() { return *mptr; }

    T *operator->() { return mptr; }

    // 关键：重写拷贝赋值
    CSmartPtr<T> &operator=(const CSmartPtr<T> &src) {
        // 防止自赋值
        if (this == &src) {
            return *this;
        } else {
            // 赋值之前一定要看是不是最后一个
            if (0 == myRefCnt->delRef()) {
                delete mptr;
                mptr = nullptr;
            }
            // 进行赋值，并增加引用计数
            mptr = src.mptr;
            myRefCnt = src.myRefCnt;
            myRefCnt->addRef();
        }
        return *this;
    }

private:
    T *mptr;
    // 复合一个对资源引用计数的类
    RefCnt<T> *myRefCnt;
};

int main() {
    CSmartPtr<int> ptr1(new int(1));
    CSmartPtr<int> ptr2(ptr1);
    cout << *ptr2 << endl;
    CSmartPtr<int> ptr3;
    ptr3 = ptr2;

    cout << *ptr3 << endl;
    return 0;
}
