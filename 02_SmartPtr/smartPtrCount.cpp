//
// Created by 86188 on 2023/8/2.
//

// 自己实现一个简单的有计数功能的智能指针
/*
 * 组成
 *      1.一个计数对象
 *          a.指向资源的指针
 *          b.计数器
 *      2.一个智能指针
 *          a.指向资源的指针
 *          b.指向计数对象的指针
 *      具体见语雀文档
 * */
template<typename T>
class RefCnt {
public:
    RefCnt(T *ptr = nullptr) : mptr(ptr) {
        if (mptr != nullptr) mcount = 1;
    }

private:
    T *mptr;
    int mcount;
};

template<typename T>
class CSmartPtr {
public:
    explicit CSmartPtr(T *ptr = nullptr) : mptr(ptr) {
        mpRefCnt = new RefCnt<T>(mptr);
    }

    ~CSmartPtr() { delete mptr; }

    T &operator*() { return *mptr; } //
    T *operator->() { return mptr; }

private:
    T *mptr; // 指向资源的指针
    RefCnt<T> *mpRefCnt; // 指向该资源引用对象的指针
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
    CSmartPtr<int> p2(p1); // 报错：因为是浅拷贝
    return 0;
}
