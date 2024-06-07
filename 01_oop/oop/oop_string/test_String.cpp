#include <iostream>
#include "myString2.h"
#include <vector>

using namespace std;

int main() {
    String s1("aaaa");
    cout << "------- 1 --------" << endl;
    String s2 = GetString(s1); // 在构造的时候，直接初始化
    cout << "------- 2 --------" << endl;
    cout << s2 << endl;
    cout << "------- 3 --------" << endl;
    String s3;
    s3 = String("bbbb"); // 右值引用的拷贝构造不一定会触发, 编译器可能会执行返回值优化（Return Value Optimization，RVO）
    cout << "------- 4 --------" << endl;
    String s4 = std::move(String("cccc")); // 右值引用的拷贝构造;
    // << String(const char *cstr)
    // << String(String&&)
    String s5 = String("dddd"); // 不使用 move，现代编译器会帮我们优化，直接构造 String s5;
    // << String(const char *cstr)
    cout << "------- 5 --------" << endl;
    String s6 = s3 + s4;
    cout << s6 << endl;
    //    ---------------
    /*
        在这个特定的情况下，编译器可能会执行返回值优化（Return Value Optimization，RVO）这是一种优化技术，
        可以避免创建临时对象，直接将局部对象的内容放在调用者的空间中。因此，即使你定义了带右值引用的拷贝构造函数，
        但由于编译器的优化，它可能不会被直接调用。R可以消除不必要的对象复制，提高程序的性能。
        如果你想确保执行带右值引用的拷贝构造函数，可以关闭返回值优化（在某些编译器中可能需要特定的编译选项），
        或者使用调试工具来观察实际发生的构造函数调用。
    */

    cout << endl;
    cout << endl;
    cout << "************************************** " << endl;
    vector<String> vec;
    vec.reserve(3);
    vec.push_back(s1);
    // << String(const String&) 需要重新在容器中构造
    cout << "-------------------------" << endl;
    // 由于 设定了右值引用的 拷贝构造，因此能达到和 emplace 一样实际只构造了一次 String
    vec.push_back(String("eeee"));
    // << String(const char *cstr) String(String&&)

    // vec.emplace_back("bbb");
    // << String(const char *cstr)
    cout << "-------------------------" << endl;

    return 0;
}