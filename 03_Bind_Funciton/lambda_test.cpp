//
// Created by 86188 on 2023/8/21.
//
#include <iostream>

using namespace std;

/*
 * 使用 lambda 表达式
 *
 * C++11 函数对象的升级版 => lambda 表达式
 *
 * 函数对象的缺点
 * 使用泛型算法传递参数 比较性质、自定义操作 优先级队列 智能指针
 *
 * lambda 表达式的语法
 * [捕获变量](形参列表)->返回值{操作代码}
 * [] 相当于函数对象的构造函数，（）相当于运算符重载函数
 *
 * 如果 lambda 表达式的返回值不需要，那么 "->" 返回值可以省略的
 * [] 表示不捕获任何外部变量
 * [=] 表示以传值的方式捕获外部变量
 * [&] 表示以传引用的方式捕获外部的所有变量
 * [this] 表示捕获外部的 this 指针
 * [=, &a] 表示以传值的方式捕获外部的所有变量，但是 a 变量以引用的方式捕获
 * [a, b] 以值传递的方式捕获 a 和 b
 * [a, &b] 以值传递的方式捕获 a, 以按引用的方式捕获 b
 * */
template<typename T = int>
class TestLambda {
public:
    TestLambda(int &a, int &b) : ma(a), mb(b) {}

    void operator()() const {
        int temp;
        temp = ma;
        ma = mb;
        mb = temp;
    }

    void get() {
        cout << "ma = " << ma << endl;
        cout << "mb = " << mb << endl;
    }

private:
    int &ma; // 重点在这
    int &mb;
    // 引用成员变量允许在const成员方法中修改其所引用的对象，因为const成员方法限制的
    // 是对于类中非mutable成员的修改，而并不涉及通过引用来修改引用对象本身的情况。
};

int main() {
    auto func1 = []() -> void { cout << "hello world"; };
    func1();

    auto func2 = [](int a, int b) -> int { return a + b; };
    cout << func2(2, 3) << endl;

    int a = 10;
    int b = 20;
    auto func3 = [&a, &b]() {
//        auto func3 = [&]() { // 也可以
        int temp = a;
        a = b;
        b = temp;
    };
    func3();
    cout << "a =" << a << endl; // 如果 没有& 那么 a 就不会改变
    cout << "b =" << b << endl; // 如果 没有& 那么 a 就不会改变
    cout << "*****************"  << endl;
    TestLambda test = TestLambda(a, b);
    test();
    test.get(); // ma = 10 mb = 20
    cout << "a =" << a << endl; // 10

    return 0;
}