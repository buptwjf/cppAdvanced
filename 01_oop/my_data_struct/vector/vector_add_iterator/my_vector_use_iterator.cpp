//
// Created by 86188 on 2023/11/16.
//


#include <iostream>
#include "Vector.h" // 增加 iterator

using namespace std;

int main() {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    // 使用 for each 遍历迭代器
    for (auto i : v1) {
        cout << i << " ";
    }
    cout << endl;
    // 增加 iterator 后不增加 vec 的内存
    cout << "sizeof(v1): " << sizeof(v1) << endl; // 32
    return 0;
}