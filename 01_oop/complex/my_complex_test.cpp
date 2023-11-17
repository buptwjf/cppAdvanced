#include <iostream>
#include  "my_complex.h"

using namespace std;

/*
    complex 类的测试程序
*/


int main() {

    cout << "------- 测试 complex 对象的创建 -------" << endl;
    complex c;
    cout << "c 的实部 = " << c.real() << endl;
    cout << "c 的虚部 = " << c.imag() << endl;
    complex c1(2, 3);
    cout << "c1 的实部 = " << c1.real() << endl;
    cout << "c1 的虚部 = " << c1.imag() << endl;
    cout << "------- 测试获取 complex 对象的实部和虚部  -------" << endl;
    cout << real(c1) << endl;
    cout << imag(c1) << endl;
    cout << "------- 测试 += -= *= 运算符重载  -------" << endl;
    complex c2(-3, -2);
    cout << (c += c1) << endl;  // 这里为啥要括号 ? 因为 << 运算符的优先级大于 +=
    cout << (c -= c1) << endl;
    cout << (c1 *= c1) << endl;
    cout << (c2 += c2 += c2) << endl;  //(-12, -8)
    cout << (c2 -= c2 -= c2) << endl;
    cout << (c2 *= c2 *= c2) << endl;
    cout << "------- 测试 + - * 运算符重载  -------" << endl;
    cout << (c1 + c2) << endl;
    cout << (c1 + c2 + c) << endl;
    cout << "###############" << endl;
    cout << (c1 + 5.0) << endl;
    cout << (5.0 + c1) << endl;
    cout << "###############" << endl;
    cout << (c1 + 5.0) << endl;
    cout << (+c1) << endl;
    cout << "-------------------------------------" << endl;
    cout << (c1 - c2) << endl;
    cout << (c2 - 5) << endl;
    cout << (5 - c2) << endl;
    cout << (-c1) << endl;
    cout << "-------------------------------------" << endl;
    cout << (c1 * c1) << endl;
    cout << (c1 * 2) << endl;
    cout << (2 * c1) << endl;
    cout << "-------------------------------------" << endl;
    cout << (c1 / 2) << endl;
    cout << "------- 测试 == != 运算符重载 --------" << endl;
    complex c3(2, 3);
    complex c4(2, -3);
    complex c5(3, 0);
    cout << (c3 == c4) << endl;
    cout << (c3 == 2) << endl;
    cout << (3 == c4) << endl;
    cout << (c5 == 3) << endl;
    cout << "-------------------------------------" << endl;
    cout << (c3 != c4) << endl;
    cout << (c3 != 2) << endl;
    cout << (3 != c4) << endl;
    cout << (c5 != 3) << endl;
    cout << "------------ 测试 polar -------------" << endl;
    cout << polar(4, 1.57) << endl;
    cout << "------------ 测试 conj --------------" << endl;
    cout << conj(c4) << endl;
    cout << "------------ 测试 norm --------------" << endl;
    cout << norm(c4) << endl;
    return 0;
}
