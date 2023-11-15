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
        cout << "Test(const Test &t)" << endl;
    }

    Test &operator=(const Test &t) {
        cout << "operator=" << endl;
        ma = t.ma;
        return *this;
    }

private:
    int ma;
};

int main() {
    cout << "1.------------------" << endl;
    Test t1;    // 拷贝构造
    Test t2(t1); // 拷贝构造
    Test t3 = t1; // 拷贝构造
    cout << "2.------------------" << endl;
    /*
        Test(20) 显式构造临时对象 生存周期：所在的语句
        由于是构造 t4
        C++ 编译器会进行优化，直接构造 t4，不产生临时对象了
     * */
    Test t4 = Test(20); // Test() 不是拷贝构造 相当于 Test t4(20)
    cout << "3.------------------" << endl;
    t4 = t2; // 调用拷贝赋值
    cout << "4.------------------" << endl;
    t4 = Test(30); // 因为是赋值，所以要显式产生临时对象，然后调用拷贝赋值，结束语句后析构
    cout << "5.------------------" << endl;
    t4 = (Test)30; // 判断 int->Test(int)，如果可以，显式生成临时对象，然后调用拷贝赋值，结束语句后析构
    cout << "6.------------------" << endl;
    t4 = 20; // 隐式生成临时对象，然后调用拷贝赋值，结束语句后析构
    cout << "7.------------------" << endl;
//    Test* p = &Test(40); // 错误！！ 临时对象出语句后会被析构
//    Test &ref = Test(50); // 错误！！临时对象出语句后会被析构
    const Test &ref = Test(50); // 加 const 后可以
    cout << "8.------------------" << endl;
    return 0;
}