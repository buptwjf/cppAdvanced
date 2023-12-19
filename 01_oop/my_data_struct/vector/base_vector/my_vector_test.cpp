//
// Created by 86188 on 2023/11/15.
//
#include "Vector.h"
#include <iostream>

/*
 * 测试 Vector.h
*/
using namespace std;

int main() {
    // 测试构造函数
    Vector<int> vec;
    Vector<int> vec1(5);
    // 测试 empty() 和 size()
    cout << "vec empty: " << vec.empty() << endl;
    cout << "vec size: " << vec.size() << endl;
    // 测试 push_back() pop_back()
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    cout << "vec empty: " << vec.empty() << endl;
    cout << "vec size: " << vec.size() << endl;
    cout << "vec capacity: " << vec.capacity() << endl;
    vec.pop_back();
    cout << "vec size: " << vec.size() << endl;

    // 测试拷贝赋值
    vec1 = vec;
    cout << vec[0] << endl;
    cout << "vec1 empty: " << vec1.empty() << endl;
    cout << "vec1 size: " << vec1.size() << endl;

    // 测试拷贝构造
    Vector<int> vec2 = vec1;
    // 测试 operator[]
    cout << vec2[4] << endl;
    // 测试 begin() back()
    cout << "vec2.begin(): " << vec2.begin() << endl;
    cout << "vec2.back(): " << vec2.back() << endl;
    return 0;
}