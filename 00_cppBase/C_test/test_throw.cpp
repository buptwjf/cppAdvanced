//
// Created by 86188 on 2025/6/25.
//

#include <iostream>
using namespace std;
double division(double a, double b)
{
    try
    {
        if (b == 0)
        {
            throw "出现了除数为0的错误";//throw关键字抛出错误类型 const char*
        }
    }
    catch (const char* error_string)//捕获const char*类型的错误
    {
        cout << error_string << endl;//打印它
    }
    return (a / b);
}
int main()
{
    cout << division(1, 0);
}
