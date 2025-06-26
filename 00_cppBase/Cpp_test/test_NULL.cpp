//
// Created by 86188 on 2025/6/25.
//
#include <iostream>
using namespace std;
void func(void* i){
    cout << "func1" << endl;
}

void func(int i){
    cout << "func2" << endl;
}

int main(int argc,char* argv[]){
    // func(NULL); 会报错
    // fun2 与预期相反，预期是 NULL 作为空指针，甚至有点编译器会二义性报错
    func(nullptr);  // fun1
    getchar();
}