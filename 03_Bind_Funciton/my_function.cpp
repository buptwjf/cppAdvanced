//
// Created by 86188 on 2023/8/18.
//


/*
 * 自己实现 function 功能
 * 原理：
 * */
#include <iostream>
#include <string>

using namespace std;

void hello(string str) { cout << str << endl; }

int sum(int a, int b) { return a + b; }

//
template<typename Fty>
class myfunction {
};

/* 需要定义两个类，太麻烦 */
//
//template<typename R, typename A1>
//class myfunction<R(A1)> {
//public:
//    // 定义一个函数指针类型
//    using PFUNC = R(*)(A1);
//
//    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
//
//    R operator()(A1 arg) {
//        return _pfunc(arg);
//    }
//
//private:
//    PFUNC _pfunc;
//};
//
//
//template<typename R, typename A1>
//class myfunction<R(A1, A1)> {
//public:
//    // 定义一个函数指针类型
//    using PFUNC = R(*)(A1, A1);
//
//    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
//
//    R operator()(A1 arg1, A1 arg2) {
//        return _pfunc(arg1, arg2);
//    }
//
//private:
//    PFUNC _pfunc;
//};


// 模板参数数量的偏特化 C++ 11
template<typename R, typename... A>
class myfunction<R(A...)> {
public:
    // 定义一个函数指针类型
    using PFUNC = R(*)(A...);

    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}

    R operator()(A... arg ) {
        return _pfunc(arg...);
    }
private:
    PFUNC _pfunc;
};


int main() {
    myfunction<void(string)> func1 = hello;
    func1("abc!");
    myfunction<int(int, int)> func2 = sum;
    cout << func2(2, 3);
    return 0;
}