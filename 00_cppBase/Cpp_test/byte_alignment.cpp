#include "usr.h"

class MyClass {
    void test() { std::cout << "MyStuct" << std::endl; };
    int a; // 4 + 4  上一个小的成员变量必须和下一个大的成员变量对齐
    double b; // 8
    char c; // 1 -> 8 整体对齐
    // 8 + 8 + 8
};

class MyClass1 {
    void test() { std::cout << "MyStuct" << std::endl; };
    virtual void test1() { std::cout << "test1" << std::endl; };
    virtual void test2() { std::cout << "test2" << std::endl; };
    virtual void test3() = 0;

    int a; // 4 + 4 上一个小的成员变量必须和下一个大的成员变量对齐
    double b; // 8
    char c; // 1 -> 8 整体对齐
    // 8 + 8 + 8 + 8(虚指针)
};

class MyClass2 : public MyClass1 {
    int d{};
    static int e;
    void test1() override { std::cout << "test1" << std::endl; };
    static void test4() { std::cout << "test1" << std::endl; };
};


class MyClass3 {
    void test() { std::cout << "MyStuct" << std::endl; };
    double b;
    char c; // 1+3 上一个小的成员变量必须和下一个大的成员变量对齐
    int a;
    // 8 + 4 + 4
};

class MyClass4 {
    virtual void test() { std::cout << "MyStuct" << std::endl; };
    char c; // 1+7 整体对齐
};




struct MyStruct {
    int a;	// 8
    double b; // 16
    char c; // 1+7
    void test() { std::cout << "MyStuct" << std::endl; };
};


int main() {
    std::cout << "MyClass size is " << sizeof(MyClass) << std::endl; // (1+7) + 8 + (4+4) <- 整体对齐（必须是 8 的倍数）
    std::cout << "MyClass1 size is " << sizeof(MyClass1) << std::endl; //  32  24 + 8(虚函数指针)
    std::cout << "MyClass2 size is " <<  sizeof(MyClass2) << std::endl; //  32  24 + 8 + 0 (int d, static 不占用)
    std::cout << "MyClass3 size is " <<  sizeof(MyClass3) << std::endl; //  16 = 8 + 4 + 4 (int d, static 不占用)
    std::cout << "MyClass4 size is " << sizeof(MyClass4) << std::endl; //  16 = 8 + (1+7) 整体对齐
    std::cout << "MyStruct size is " << sizeof(struct MyStruct) << std::endl; // 24
    return 0;
}