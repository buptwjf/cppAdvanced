#include <iostream>

using namespace std;

class Test {
public:
    // Test() Test(10) Test(10, 10) 相当于三种构造函数
    Test(int a = 0, int b = 0) : ma(a), mb(b) {
        cout << "Test()" << endl;
    }

    ~Test() {
        cout << "~Test" << endl;
    };

    Test(const Test &t) : ma(t.ma), mb(t.mb) {
        cout << "Test(const Test &t)" << endl;
    }

    Test &operator=(const Test &t) {
        cout << "operator=" << endl;
        ma = t.ma;
        mb = t.mb;
        return *this;
    }

private:
    int ma;
    int mb;
};

Test t1(10, 10); // 全局变量程序一开始就构造

int main() {
    cout << "1.------------------" << endl;
    Test t2(20, 20); // 构造
    Test t3 = t2; // 拷贝构造
    cout << "2.------------------" << endl;
    // 直接构造 t4
    // t4 程序运行时分配内存，程序开始时进行构造，保留直到程序结束
    static Test t4 = Test(30, 30); // 直接构造 t4
    cout << "3.------------------" << endl;
    t2 = Test(40, 40); // 显式构造 + 赋值 + 析构
    t2 = (Test) (50, 50); //  显式构造 + 赋值 + 析构
    t2 = 60; // 隐式构造 + 赋值 + 析构
    cout << "4.------------------" << endl;
    Test *p1 = new Test(70, 70); // 构造函数
    Test *p2 = new Test[2]; // 两次构造函数
//    Test* p3 = &Test(80,80); // 错误！！ 临时对象出语句就会消失
    const Test &p4 = Test(70, 70); // 必须加 const 构造函数，直接构造
    delete p1; // 析构
    delete[]p2; // 两次析构
    cout << "5.------------------" << endl;
    return 0;
}

Test t5(10, 10); // 全局变量程序一开始就会构造
