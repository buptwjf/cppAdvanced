//
// Created by 86188 on 2023/8/21.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 使用 lambda 表达式对容器进行操作
 * 可以避免还得定义一个类出来
 * */

int main() {
    vector<int> vec;

    srand(time(nullptr));
    for (int i = 0; i < 20; i++) {
        vec.push_back(rand() % 100 + 1);
    }

    // 1. 用于 sort
    sort(vec.begin(), vec.end(),
         [](int a, int b) -> bool { return a > b; });

    for (int i: vec) {
        cout << i << " ";
    }
    cout << endl;

    // 把 65 按序插入进去
    // 由于库里的都是二元表达式，需要用 bind 比较麻烦
    // 用于 find_if
    auto it = find_if(vec.begin(), vec.end(), [](int a) -> bool { return a < 65; });
    // 找到第一个小于 65 的
    if (it != vec.end()) {
        vec.insert(it, 65);
        for (int i: vec) {
            cout << i << " ";
        }
        cout << endl;
    }

    // 用于 each
    for_each(vec.begin(), vec.end(), [](int a) { cout << "*" << a << " "; });
    cout << endl;
    for_each(vec.begin(), vec.end(), [](int a) { if (a % 2 == 0) { cout << "*" << a << " "; }});
    return 0;

}