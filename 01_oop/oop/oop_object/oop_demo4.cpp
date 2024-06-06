#include <iostream>

using namespace std;

class Test {
public:
    Test(int a = 0) : ma(a) {
        cout << "Test()" << endl;
    }

    ~Test() {
        cout << "~Test" << endl;
    };

    Test(const Test &t) : ma(t.ma) {
        cout << "Test(const Test &)" << endl;
    }

    Test &operator=(const Test &t) {
        cout << "operator=" << endl;
        ma = t.ma;
        return *this;
    }

    int getData() const { return ma; }

private:
    int ma;
};

Test GetObject(Test& t) { // tips 1
    int val = t.getData();
//    Test tmp(val);
//    return tmp;
    return Test(val); // tips 2
}

/*
 * 1、函数参数传递过程中，优先按引用传递，不要按值传递
 *      // 减少对形参 t 的拷贝构造
 * 2、返回的时候直接返回临时对象，不要返回定义过的对象
 *    这样编译器不会在子函数栈帧上产生临时对象，
 *    会在 main 直接构造临时对象，然后进行赋值操作。(这一点实际编译器中没有体现)
 * 3、在声明的时候同时进行初始化
 *    这样也不需要在 main 上构造临时对象，再进行赋值操作的操作；
 *    会直接构造 t2
 * */

int main() {
    Test t1(10); // 构造函数
//    Test t2;
    Test t2 = GetObject(t1); // 构造函数  tips 3
    cout << " --------------- " << endl;
//    t2 = GetObject(t1); //

    cout << " --------------- " << endl;
    return 0;
}