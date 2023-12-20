#ifndef __MYSTRING__
#define __MYSTRING__

/*
    对 base_string 增加迭代器
    记住：迭代器可以透明的访问容器内部的元素！
*/


class String {


public:
    String(const char *cstr = nullptr);  // 构造函数（声明时候带默认，实现的时候就不带默认）
    String(const String &str);  // 拷贝构造
    String &operator=(const String &str);  // 拷贝复制
    ~String();  // 析构函数

    [[nodiscard]] const char *get_c_ctr() const { return m_data; }  // 返回 string 对象的指针

    bool operator>(const String &str);

    bool operator<(const String &str);

    bool operator==(const String &str);

    char &operator[](int index);

    const char &operator[](int index) const;

    int length();

    class iterator {
    public:
        iterator(char *p = nullptr) : _p(p) {}

        // 迭代器 三个经典 方法
        bool operator!=(const iterator &it) { return _p != it._p; }

        void operator++() { ++_p; };

        char &operator*() { return *_p; }

    private:
        char *_p;
    };

    iterator begin() { return {m_data}; }

    iterator end() { return {m_data + length()}; }

private:
    char *m_data;

    friend String operator+(const String &lhs, const String &rhs);

    friend class iterator;  // 将迭代器类声明为友元
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
    // 先定义 String ，再开辟空间，避免频繁开辟空间
    // char* ptmp = new char[strlen(lhs.m_data) + strlen(rhs.m_data) + 1]
    tmpStr.m_data = new char[strlen(lhs.m_data) + strlen(rhs.m_data) + 1];
    strcpy(tmpStr.m_data, lhs.m_data);
    strcat(tmpStr.m_data, rhs.m_data);
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