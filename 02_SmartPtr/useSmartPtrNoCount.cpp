//
// Created by 86188 on 2023/8/2.
//
#include "iostream"
#include "memory"

using namespace std;

int main() {
    // 使用 auto_ptr
    auto_ptr<int> ptr1(new int);
    auto_ptr<int> ptr2(ptr1);

    *ptr2 = 20;
    cout << *ptr2 << endl;

//    scoped_ptr<int> ptr3(new int); // 不知道为什么找不到头文件，可能是配置C++11的原因

    // 使用 unique_ptr
    unique_ptr<int> ptr4(new int(15));
    unique_ptr<int> ptr5 = move(ptr4);
    cout << "*ptr5 = " << *ptr5 << endl;
    unique_ptr<int> ptr6(new int(25));
    ptr5 = move(ptr6);
    cout << "*ptr5 = " << *ptr5 << endl;
    return 0;
}