#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__
// 防卫性声明
/*
    定义一个复数的类
    1. 复数对象的构造函数、
        1.1 如果未定义实部或虚部，那么默认值为0。
    2. 数据定义为私有
    3. 定义函数：获得实部，获得虚部
        3.1 com1.real() com1.imag()
        3.2 real(com1) imag(com1)
    4. 操作符号重载
        注意：要考虑复数与复数，复数与实数，复数与虚数之间的运算
        4.1 + - *
        4.2 += -= *=
        4.3 正 负
        4.4 <<
    5. 使用极坐标表示复数(polar)
    6. 求复数的共轭(conj)
    7. 求复数的norm(模平方)
    8. 注意：
        7.1 inline
        7.2 & pass / return
        7.3 const
*/

class complex {
  public:
    // 构造函数，添加默认值
    complex(double r = 0, double i = 0) // pass by value 效率差不多
        : re(r), im(i) {}               // 设置初值列

    // 返回 re, im 函数类型为 const  ???这里的const的位置
    // 设计为成员函数, 希望是 inline
    // 在函数中不会改变data, 用const
    double real() const { return re; } // 成员函数有隐含的 this 指针
    double imag() const { return im; }

    // +=  -=  *=  /=  操作符重载
    // 设计为成员函数，因为左操作数都为对象
    complex &operator+=(const complex &);
    complex &operator-=(const complex &);
    complex &operator*=(const complex &);
    // complex& operator /= (const double);  不能进行 /=

  private:
    // 定义 re, im 为私有
    double re, im;
    // 想直接取得 re 和 im
    friend complex &__doapl(complex *ths, const complex &r);
    friend complex &__doami(complex *ths, const complex &r);
    friend complex &__doaml(complex *ths, const complex &r);
};

// 获取 complex 对象的实部和虚部
inline double // inline
real(const complex &x) {
    return x.real();
}

inline double imag(const complex &x) { return x.imag(); }

// 操作符 += -= *= 的重载
/*
    注意：
        1. 建议为 inline function
        2. 属于 class 里面定义的 ::
            2.1 类成员函数是类的一个成员，它可以操作类的任意对象
            2.2 可以访问对象中的所有成员。
        3. 返回值 by reference 不能 void
*/
inline complex &__doapl(complex *ths, const complex &r) {
    ths->re += r.re;
    ths->im += r.im;
    return *ths; //*ths 为一个值, 接收方可以 value or reference
}

inline complex & // return reference 保证操作符的连续操作
complex::operator+=(const complex &r) // :: 表示为成员函数, 左边为类的成员
{
    return __doapl(this, r); // this 对应操作符的左操作数的指针(隐含)
}

inline complex &__doami(complex *ths, const complex &r) {
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex &complex::operator-=(const complex &r) {
    return __doami(this, r);
}

inline complex &__doaml(complex *ths, const complex &r) {
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}

inline complex &complex::operator*=(const complex &r) {
    return __doaml(this, r);
}

// 操作符 + -  重载
/*
    注意：
        1. return by value
        2. 复数与实数的运算
        3. 应该定义在类外，因为左操作数会默认成类的对象，但实际上有可能不是
   (double)
*/
inline complex // return by value
operator+(const complex &x, const complex &y) {
    // 使用临时对象
    return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex operator+(const complex &x, double y) // ???这里y可以用const
{
    return complex(real(x) + y, imag(x));
} //??? 为什么没有这个也可以

inline complex operator+(double x, const complex &y) {
    return complex(x + real(y), imag(y));
} //??? 为什么没有这个也可以

inline complex operator+(const complex &x) {
    return x; // 取正
}

inline complex operator-(const complex &x, const complex &y) {
    return complex(real(x) - real(y), imag(x) - imag(y));
}

inline complex operator-(const complex &x, double y) {
    return complex(real(x) - y, imag(x));
}

inline complex operator-(double &x, const complex &y) {
    return complex(x - real(y), -imag(y));
}

inline complex operator-(const complex &x) {
    return complex(-real(x), -imag(x));
}

inline complex operator*(const complex &x, const complex &y) {
    return complex(real(x) * real(y) - imag(x) * imag(y),
                   real(x) * imag(y) + real(y) * imag(x));
}

inline complex operator*(const complex &x, double y) {
    return complex(real(x) * y, imag(x) * y);
}

inline complex operator*(double &x, const complex &y) {
    return complex(x * real(y), x * imag(y));
}

inline complex operator/(const complex &x, double y) {
    return complex(real(x) / y, imag(x) / y);
}

inline bool operator==(const complex &x, const complex &y) {
    return (real(x) == real(y) && imag(x) == imag(y));
}

inline bool operator==(const complex &x, double y) {
    return (real(x) == y && imag(x) == 0);
}

inline complex operator==(double &x, const complex &y) {
    return (x == real(y) && imag(y) == 0);
}

inline bool operator!=(const complex &x, const complex &y) {
    return (real(x) != real(y) || imag(x) != imag(y));
}

inline bool operator!=(const complex &x, double y) {
    return (real(x) != y || imag(x) != 0);
}

inline complex operator!=(double &x, const complex &y) {
    return (x != real(y) && imag(y) != 0);
}

#include <cmath>

inline complex polar(double r, double t) {
    return complex(r * cos(t), r * sin(t));
}

inline complex conj(const complex &x) { return complex(real(x), -imag(x)); }

inline double norm(const complex &x) {
    return (real(x) * real(x) + imag(x) * imag(x));
}

// 写成非成员函数, 因为希望左操作数为 cout
using namespace std;
ostream &operator<<(ostream &os, const complex &x) {
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

#endif