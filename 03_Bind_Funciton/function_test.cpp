//
// Created by 86188 on 2023/8/19.
//

/*
 * 使用 function 的几种情况
 * */

#include <iostream>
#include <string>
#include <functional>

using namespace std;


void hello1() { cout << "hello" << endl; }

void hello2(string str) {
    cout << "hello " << str << endl;
}

class Test {
public:
    void operator()(string str) {
        cout << "In operator ()" << endl;
        cout << str << endl;
    }

    int sum(int a, int b) {
        cout << "sum in Test::sum" << endl;
        return a + b;
    }

};

int main() {
    cout << __cplusplus << endl;
    function<void()> func1 = hello1;
    func1();

    function<void(string)> func2 = hello2;
    func2("C++");

    // lambda 表达式
    function<int(int, int)> func3 = [](int a, int b) {
        cout << "In lambda: " << endl;
        return a + b;
    };
    cout << func3(3, 5) << endl;

    Test test; // 由于 Test() 是临时对象，属于 右值，因此不能取地址，需要实例化一个 test
    // 成员函数
    function<int(Test *, int, int)> func4 = &Test::sum;
    cout << func4(&test, 3, 4) << endl;
    // 仿函数，函数对象
    function<void(Test *, string)> func5 = &Test::operator();
    func5(&test, "hello Test");
    return 0;
}