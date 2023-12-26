//
// Created by 86188 on 2023/12/25.
//
#include "Vector1.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    Vector<int> vec(200);
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 99 + 1);
    }

    for (auto i: vec) {
        cout << i << " ";
    }
    cout << endl;
    // 给 vec 所有偶数数前面加小于 0 的数
    auto it = vec.begin();
    cout << "test insert :" << endl;
    for (; it != vec.end(); ++it) {
        if (*it % 2 == 0) {
            it = vec.insert(it, *it - 1);
            ++it;
        }
    }

    for (auto i: vec) {
        cout << i << " ";
    }
    cout << endl;

    cout << "test erase :" << endl;
    it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (*it % 2 == 0) {
            it = vec.erase(it);
        }
    }

    for (auto i: vec) {
        cout << i << " ";
    }
    return 0;
}
