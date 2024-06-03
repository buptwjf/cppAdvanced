#ifndef __MYSTRING__
#define __MYSTRING__

/*
 * 根据施磊课程，优化对象
 * GetString 函数
 *
 * 根据施磊基础班课程，新增功能
 * operator+ 重点
 * operator=
 * operator[] 重点
 * */

#include <iostream>

class String {
private:
    char *m_data;
    // 两种选择
    // 1. friend 代码更简单
    // 2. 使用get_c_ctr 代码耦合性更好，如实现 operator<<
    friend String operator+(const String &lhs, const String &rhs);
    friend std::ostream &operator<<(std::ostream &os, const String &str);

public:
    String(const char *cstr = nullptr);     // 构造函数（声明时候带默认，实现的时候就不带默认）
    String(const String &str);              // 拷贝构造
    String &operator=(const String &str);   // 拷贝复制
    ~
    String();                              // 析构函数
// c_str 指针指向字符的字符串，C风格的字符串
// 在函数没有改变 m_data
    [[nodiscard]] const char *get_c_ctr() const { return m_data; }  // 返回 string 对象的指针

    bool operator>(const String &str);  // 字符串比较大小
    bool operator<(const String &str);  // 字符串比较大小
    bool operator==(const String &str); // 字符串比较大小

    char &operator[](int index);                // 字符串根据 [] 赋值
    const char &operator[](int index) const;    // 字符串根据 [] 显示
// 为什么要有 const char& 版本，如果String中的内容是常量的化，可以调用该函数

    int length(); // 输出字符串的长度
};

# include <cstring>

// 构造函数
inline
String::String(const char *cstr) {
    if (cstr) {
        m_data = new char[strlen(cstr) + 1]; // 多一个 \0 的位置
        strcpy(m_data, cstr);
        // C 11 新标准
        // strcpy_s(m_data, cstr);
    } else {
        // 如果是空 string
        m_data = new char[1];
        *m_data = '\0';
    }
}

// 析构函数
inline
String::~String() {
    delete[] m_data; // 释放空间
    m_data = nullptr; // 指针置空
}

// 拷贝复制
inline String &String::operator=(const String &str) {
    // 第一步必须检查自赋值 ！
    if (this == &str)  //&str 表示取地址
        return *this;

    delete[] m_data;  // 先删除左边；
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    // strcpy_s(m_data, str.m_data);
    return *this;
}

// 拷贝构造
inline
String::String(const String &str) {
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    // strcpy_s(m_data, str.m_data); // C++11 新标准
}

// 字符串比较大小
bool String::operator>(const String &str) {
    return strcmp(m_data, str.m_data) > 0;
}

bool String::operator<(const String &str) {
    return strcmp(m_data, str.m_data) < 0;
}

bool String::operator==(const String &str) {
    return strcmp(m_data, str.m_data) == 0;
}

char &String::operator[](int index) {
    return m_data[index];
}

const char &String::operator[](int index) const {
    return m_data[index];
}

// 重载 + 运算符
/*
 *  设置为非成员函数能够确保操作符的对称性，即可以实现左右操作数的对称操作
 *  定义为非成员函数还可以使其适用于标准库中其他类型的操作符重载，
 *      如流插入运算符（operator<<）和流提取运算符（operator>>），这些通常也是非成员函数。


 * */
String operator+(const String &lhs, const String &rhs) {
    // 方法一：先定义 String ，再开辟空间，避免多开辟内存
    String tmpStr;
    tmpStr.m_data = new char[strlen(lhs.m_data) + strlen(rhs.m_data) + 1];
    strcpy(tmpStr.m_data, lhs.m_data);
    strcat(tmpStr.m_data, rhs.m_data);
    return tmpStr;
    /*  方法一的优点
     *  1. 避免内存泄露，new 失败后会用~String() 自动销毁
     *  2. 符合 RAII 原则，资源获取即初始化
     * */

    // 方法二
    // char* ptmp = new char[strlen(lhs.m_data) + strlen(rhs.m_data) + 1]
    // strcpy(tmpStr.m_data, lhs.m_data);
    // strcat(tmpStr.m_data, rhs.m_data);
    // String tmpStr(ptmp);
    // delete *ptmp
    // return tmpStr;
}

int String::length() {
    return strlen(m_data);
}

// 没有用成员方法
String GetString(String &str) {
    const char *pstr = str.get_c_ctr();
    return {pstr};
}

#include <iostream>

using namespace std;

// 输出流函数

// 方法一：采用 get_c_ctr() 方法获得 m_data
//inline ostream &operator<<(ostream &os, const String &str) {
//    os << str.get_c_ctr();
//    return os;
//}

// 方法二：采用友元函数获得 m_data
inline std::ostream &operator<<(std::ostream &os, const String &str) {
    os << str.m_data;
    return os;
}

#endif