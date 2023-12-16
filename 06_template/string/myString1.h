#ifndef __MYSTRING__
#define __MYSTRING__
/*
 * 根据施磊课程，优化对象
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
public:
    explicit String(const char *cstr = nullptr);  // 构造函数（声明时候带默认，实现的时候就不带默认）
    String(const String &str);  // 拷贝构造
    String &operator=(const String &str);  // 拷贝复制
    ~String();  // 析构函数
    // c_str 指针指向字符的字符串，C风格的字符串
    // 在函数没有改变 m_data
    [[nodiscard]] const char *get_c_ctr() const { return m_data; }  // 返回 string 对象的指针
};

# include <cstring>

inline
String::String(const char *cstr)  // 构造函数
{
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
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

// 没有用成员方法
String GetString(String &str) {
    const char *pstr = str.get_c_ctr();
    return String(pstr);
}


#include <iostream>

using namespace std;

inline
ostream &operator<<(ostream &os, const String &str) {
    os << str.get_c_ctr();
    return os;
}

#endif