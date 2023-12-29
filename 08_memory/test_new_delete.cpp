//
// Created by 86188 on 2023/12/26.
//
//
#include <iostream>

using namespace std;

void *operator new(size_t size) {
    void *p = malloc(size);
    if (p == nullptr)
        throw bad_alloc();
    cout << "operator new addr: " << p << endl;
    return p;
}

void *operator new[](size_t size) {
    void *p = malloc(size);
    if (p == nullptr)
        throw bad_alloc();
    cout << "operator new[] addr: " << p << endl;
    return p;
}

// 可能由于编译器的原因 这里 operator delete 无法被调用
void operator delete(void *ptr) {
    cout << "operator delete addr: " << ptr << endl;
    free(ptr);
}

void operator delete[](void *ptr) {
    cout << "operator delete[] addr: " << ptr << endl;
    free(ptr);
}

class Test {
public:
    explicit Test(int data = 10) : ptr(new int(data)) { cout << "Test()" << endl; }
    ~Test() {
        delete ptr;
        cout << "~Test()" << endl;
    }
private:
    int *ptr;
};

int main() {
    Test *p1 = new Test[5];
    delete[] p1; // 假如没有 [] 只会调用一次析构函数
}