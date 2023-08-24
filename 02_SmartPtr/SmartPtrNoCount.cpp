//
// Created by 86188 on 2023/8/8.
//
#include "iostream"

using namespace std;

template<typename T>
class CSmartPtr {
public:
    explicit CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}
    ~CSmartPtr() { cout << "~CSmartPtr" << endl; delete mptr; mptr = nullptr;}
    CSmartPtr(const CSmartPtr<T> &src) {
        mptr = src.mptr;
    }
    T &operator*() { return *mptr; }
    T *operator->() { return mptr; }
private:
    T *mptr;
};
int main() {
    CSmartPtr<int> p1(new int);
    CSmartPtr<int> p2(p1);
    cout << *p2 << endl;
    // 报错，因为会重复释放两次内存
    return 0;
}
