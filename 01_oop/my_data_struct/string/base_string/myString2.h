#ifndef __MYSTRING__
#define __MYSTRING__
/*
 * 根据施磊课程，优化对象
 * 根据施磊基础班课程，新增功能
 * operator+
 * operator=
 * operator[]
 * */
/*
     需求：定义 String 的对象  最简单的striung 类型
     1.构造函数
     2.拷贝构造
     3.拷贝复制
     4.析构函数
     5.<< 运算符重载 
*/
class String {
private:
    char *m_data;

    // 两种选择
    // 1. friend 代码更简单
    // 2. 使用get_c_ctr 代码耦合性更好，如实现 operator<<
    friend String operator+(const String &lhs, const String &rhs);

public:
    String(const char *cstr = nullptr);  // 构造函数（声明时候带默认，实现的时候就不带默认）
    String(const String &str);  // 拷贝构造
    String &operator=(const String &str);  // 拷贝复制
    ~String();  // 析构函数
    // c_str 指针指向字符的字符串，C风格的字符串
    // 在函数没有改变 m_data
    [[nodiscard]] const char *get_c_ctr() const { return m_data; }  // 返回 string 对象的指针

    bool operator>(const String &str);

    bool operator<(const String &str);

    bool operator==(const String &str);

    char &operator[](int index);

    const char &operator[](int index) const;

    int length();

};

# include <cstring>

inline
String::String(const char *cstr)  // 构造函数
{
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

inline
String::~String()  // 析构函数
{
    // 释放空间
    delete[] m_data;
    // 指针置空
    m_data = nullptr;
}

inline
String &String::operator=(const String &str)  // 拷贝复制 需要传出引用
{
    // 第一步必须检查自赋值 ！
    if (this == &str)  //&str 表示取地址
        return *this;

    delete[] m_data;  // 先删除左边；
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
//    strcpy_s(m_data, str.m_data);
    return *this;
}

inline
String::String(const String &str)  // 拷贝构造
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
//    strcpy_s(m_data, str.m_data); // C++11 新标准
}

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

String operator+(const String &lhs, const String &rhs) {
    String tmpStr;
    // 先定义 String ，再开辟空间，避免内存开辟内存
    // char* ptmp = new char[strlen(lhs.m_data) + strlen(rhs.m_data) + 1]
    tmpStr.m_data = new char[strlen(lhs.m_data) + strlen(rhs.m_data) + 1];
    strcpy(tmpStr.m_data, lhs.m_data);
    strcat(tmpStr.m_data, rhs.m_data);
    // String tmpStr(ptmp);
    // delete *ptmp
    return tmpStr;
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


inline
ostream &operator<<(ostream &os, const String &str) {
    os << str.get_c_ctr();
    return os;
}

#endif