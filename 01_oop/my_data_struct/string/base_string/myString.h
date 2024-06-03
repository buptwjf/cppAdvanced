#ifndef __MYSTRING__
#define __MYSTRING__

/*
     需求：定义 String 的对象 ( 侯捷版本 )
     1.构造函数
     2.拷贝构造
     3.拷贝复制
     4.析构函数
     5.<< 运算符重载 
     注意：
        a. 数据为私有 
*/
class String {
private:
    char *m_data; // string 存储的位置
public:
    String(const char *cstr = nullptr);  // 构造函数
    String(const String &str);  // 拷贝构造
    String &operator=(const String &str);  // 拷贝复制
    ~String();  // 析构函数
    // c_str 指针指向字符的字符串，C风格的字符串
    // const 1表示返回值不可更改原字符串 const 2 在函数不改变对象的状态
    const char *get_c_ctr() const { return m_data; }  // 返回String的指针（C风格字符串）
};

# include <cstring>

// 构造函数
inline
// String::String(const char* cstr = 0)
// 默认参数不需要在这里写出来 )
String::String(const char *cstr) {
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
        // C++ 11 新标准
        // strcpy_s(m_data, cstr);
    } else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

// 析构函数
inline
String::~String() {
    delete[] m_data;    // 需要 []
    m_data = nullptr;   // 指针置为空
}

// 拷贝复制
// 需要传出引用
inline String &String::operator=(const String &str) {
    // 检测是否为自赋值
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

// 没有用成员方法
String GetString(String &str) {
    const char *pstr = str.get_c_ctr();
    String tmpStr(pstr);
    return tmpStr;
}

#include <iostream>

using namespace std;

// 注意这里不能写成 String 的成员函数，因为左成员操作符为 ostream
inline ostream &operator<<(ostream &os, const String &str) {
    os << str.get_c_ctr();
    return os;
}

#endif