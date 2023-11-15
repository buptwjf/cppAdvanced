//
// Created by 86188 on 2023/10/26.
//
#include <iostream>
using namespace std;
// 查看下面程序的汇编代码，可以看到 指针和引用 的汇编指令是一样的

int main(){
    int a = 1;
    int* p = &a;

    int& b = a;

    *p = 20;
    b = 30;
    return 0;
}