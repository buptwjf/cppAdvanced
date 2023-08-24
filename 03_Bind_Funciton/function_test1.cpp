//
// Created by 86188 on 2023/8/19.
//

/*
 * 使用 function 的几种情况
 * */

#include <iostream>
#include <functional>
#include <unordered_map>

using namespace std;

// 具体说明 function 的好处

void doSearch() { cout << "do search" << endl; }

void doBorrow() { cout << "do borrow" << endl; }

void doReturn() { cout << "do return" << endl; }

void doBack() { cout << "do back" << endl; }


int main() {
    unordered_map<int, function<void()>> funcMap;
    funcMap.insert({1, doSearch});
    funcMap.insert({2, doBorrow});
    funcMap.insert({3, doReturn});
    funcMap.insert({4, doBack});
    while (1) {
        int choice;
        cout << "Input choice" << endl;
        cout << "1. search" << endl;
        cout << "2. borrow" << endl;
        cout << "3. return" << endl;
        cout << "4. back" << endl;
        cin >> choice;
        // 陈旧的方法，不好
//        switch (choice) {
//            case 1: //
//            case 2: //
//            default:
//                break;
//        }
        auto it = funcMap.find(choice);
        if (it != funcMap.end()) {
            it->second();
        } else {
            cout << "Input error" << endl;
            break;
        }
    }
    return 0;
}
