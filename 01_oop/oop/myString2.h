#ifndef __MYSTRING__
#define __MYSTRING__

/* 对基础版本的 String 进行优化 */
/*
 * 1. 减少不必要的函数调用，直接返回临时对象
 * 2. 增加带右值引用参数的拷贝构造和赋值
 * 3. 增加 operator+ 操作
 * */

class String {
private:
    char *m_data;
    friend String operator+(const String &lhs, const String &rhs);

public:
    explicit String(const char *cstr = nullptr);  // 构造函数（声明时候带默认，实现的时候就不带默认）
    String(const String &str);  // 拷贝构造
    String(String &&str) noexcept; // 带右值引用的拷贝构造函数
    String &operator=(const String &str);  // 拷贝复制
    String &operator=(String &&str) noexcept ; // 带右值引用的拷贝复制函数
    ~String();  // 析构函数
    // c_str 指针指向字符的字符串，C风格的字符串
    // 在函数没有改变 m_data
    [[nodiscard]] const char *get_c_ctr() const { return m_data; }  // 返回 string 对象的指针
    // 返回值为 const 保护 String 的数据不会被改变
};

#include <cstring>
#include <iostream>

inline
String::String(const char *cstr)  // 构造函数
// String::String(const char* cstr = 0)  // 这里不能这么写，默认值不需要在这里写出来
{
    std::cout << "String(const char *cstr)" << std::endl;
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
// C++ 11 新标准，更加安全的操作，可以避免内存不足
//        strcpy_s(m_data, cstr);
    } else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::~String()  // 析构函数
{
    if(m_data){
        std::cout << "~String()" << std::endl;
        delete[] m_data;
        m_data = nullptr;
    }
}

inline
String &String::operator=(const String &str)  // 拷贝复制 需要传出引用
{
    std::cout << "operator=" << std::endl;
    if (this == &str)  //&str 表示取地址
        return *this;

    delete[] m_data;  // 先删除左边；
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
//    strcpy_s(m_data, str.m_data);
    return *this;
}

inline
String &String::operator=(String &&str) noexcept  // 右值引用的拷贝复制 需要传出引用
{
    std::cout << "operator= &&" << std::endl;
    if (this == &str)  //&str 表示取地址
        return *this;

    delete[] m_data;  // 先删除左边；
    m_data = str.m_data;
    str.m_data = nullptr;
    return *this;
}

inline
String::String(const String &str)  // 拷贝构造
{
    std::cout << "String(const String&)" << std::endl;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
//    strcpy_s(m_data, str.m_data); // C++11 新标准
}

inline String::String(String &&str) noexcept {
    std::cout << "String(String&&)" << std::endl;
    m_data = str.m_data;
    str.m_data = nullptr;
}

// 没有用成员方法
String GetString(String &str) { // 按引用传递
    const char *pstr = str.get_c_ctr();
    return String(pstr); // 直接返回临时构造对象
//    String tmp(pstr);
//    return tmp;
}

// 这样好处是 左操作是如果不是 String 但是能变为 String，那么这样也能用
String operator+(const String &lhs, const String &rhs) { // 临时对象，必须按值返回
    String tmpStr;
    tmpStr.m_data = new char[strlen(lhs.get_c_ctr()) + strlen(rhs.get_c_ctr()) + 1];
    strcpy(tmpStr.m_data, lhs.get_c_ctr()); // 如果这里直接使用 m_data,用到了 String 的私有成员，就需要定义友元
    strcat(tmpStr.m_data, rhs.get_c_ctr());
    return tmpStr;
}

#include <iostream>

using namespace std;

inline
ostream &operator<<(ostream &os, const String &str) {
    os << str.get_c_ctr();
    return os;
}

#endif