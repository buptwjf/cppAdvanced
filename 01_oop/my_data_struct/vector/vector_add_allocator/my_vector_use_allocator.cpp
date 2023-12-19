//
// Created by 86188 on 2023/11/16.
//


#include <iostream>
//#include "Vector_base.h" // 没有空间配置器的版本
#include "Vector.h" // 有空间配置器的版本
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
    cout << "------ 0 -------" << endl;
    // 1. 无空间配置器会直接构造两个 Test
    // 1. 有空间配置器的版本不会构造 Test
    Vector<Test> vec;
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "------ 1 -------" << endl;
    vec.push_back(Test());
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "------ 2 -------" << endl;
    vec.push_back(Test());
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "------- 3 ------" << endl;
    vec.push_back(Test()); // 发生了扩容
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    cout << "------- 4 ------" << endl;
    // 2. 无空间配置器: 没有析构 Test()，Test有可能占用外部资源
    // 2. 有空间配置器: 一次 ~Test()
    vec.pop_back();
    cout << "------- 5 ------" << endl;
    return 0;
}