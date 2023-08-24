//
// Created by 86188 on 2023/8/17.
//

/*
    C++11 bind 绑定器 => 返回一个函数对象
*/

#include <iostream>
#include <functional>

using namespace std;

void hello(string str) { cout << str << endl; }

int sum(int a, int b) { return a + b; }

class Test {
public:
    int sum(int a, int b) {
        return a + b;
    }
};

int main() {
    // bind 是函数模板，可以自动推演模板类型参数
    bind(hello, "hello bind!")();
    cout << bind(sum, 2, 3)() << endl;
    // 非全局函数需要使用 地址
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;

    // 参数占位符 绑定器出了语句无法继续使用
    // 最大 20 个参数
    bind(hello, placeholders::_1)("hello bind 1!");
    cout << bind(sum, placeholders::_1, placeholders::_2)(200, 300) << endl;
    cout << bind(&Test::sum, placeholders::_1, placeholders::_2, placeholders::_3)(Test(), 2000, 3000) << endl;

    // 通过 function 复用绑定器
    function<void(string)> func1 = bind(hello, placeholders::_1);
    func1("hello 1");
    func1("hello 2");
    func1("hello 3");
    return 0;
}