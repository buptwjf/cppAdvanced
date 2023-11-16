//
// Created by 86188 on 2023/11/16.
//
#include <iostream>
#include "Vector.h"

using namespace std;

class Test {
public:
    Test() { cout << "Test()" << endl; }

    ~Test() { cout << "~Test()" << endl; }
};

/*
 * 如果没有容器的空间配置器，会发生一下两个问题
 * 1. 会直接构造两个 Test
 * 2. 没有析构 Test()，Test有可能占用外部资源
 * */

int main() {
    Vector<Test> vec; // 1. 会直接构造两个 Test
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "-------------" << endl;
    vec.push_back(Test());
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "-------------" << endl;
    vec.push_back(Test());
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "-------------" << endl;
    vec.push_back(Test()); // 发生了扩容
    cout << "-------------" << endl;
    vec.pop_back(); // 2. 没有析构 Test()，Test有可能占用外部资源
    cout << "-------------" << endl;
    return 0;
}