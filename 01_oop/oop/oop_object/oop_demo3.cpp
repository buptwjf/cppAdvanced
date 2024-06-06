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

Test GetObject(Test t) { // 不能返回局部或者临时对象的指针或者引用
    int val = t.getData();
    Test tmp(val);
    cout << "wait" << endl;
    return tmp;
}



int main() {
    Test t1(10); // 构造函数
    Test t2; // 构造函数
    cout << " --------------- " << endl;
    /*
     * 1. 拷贝构造：t1 实参 => t 形参 传递
     * 2. 构造：tmp
     * 3. 拷贝赋值 tmp 到 t2 (按道理应该在 main函数的栈帧上先拷贝构造一个 Test，再给 t2 赋值，实际没有)
     * 4. 析构 tmp
     * 5. 析构：实参
     * */
    t2 = GetObject(t1); //

    cout << " --------------- " << endl;
    return 0;
}