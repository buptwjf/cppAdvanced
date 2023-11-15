#include <iostream>
#include "myString2.h"
#include <vector>

using namespace std;

int main() {
    String s1("aaaaa");
    cout << "---------------" << endl;
    String s2 = GetString(s1); // 在构造的时候，直接初始化
    cout << "---------------" << endl;
    cout << s2 << endl;
    cout << "---------------" << endl;
    String s3;
    s3 = String("bbbb"); // 右值引用的拷贝构造不一定会触发, 编译器可能会执行返回值优化（Return Value Optimization，RVO）
    cout << "---------------" << endl;
    String s4 = std::move(String("cccc")); // 不过不使用 move，现代编译器会帮我们优化，直接构造 String s4;
    cout << "---------------" << endl;
    String s5 = s3 + s4;
    cout << s5 << endl;
    cout << "---------------" << endl;
    // 这里可能没有输出 String(String&&) 而是
    //    ---------------
    //    String(const char *cstr)
    //    bbbbcccc
    //    ---------------
    // 在这个特定的情况下，编译器可能会执行返回值优化（Return Value Optimization，RVO）
    // 这是一种优化技术，可以避免创建临时对象，直接将局部对象的内容放在调用者的空间中。
    //因此，即使你定义了带右值引用的拷贝构造函数，但由于编译器的优化，它可能不会被直接调用。
    // RVO 是一种常见的优化技术，可以消除不必要的对象复制，提高程序的性能。
    //如果你想确保执行带右值引用的拷贝构造函数，可以关闭返回值优化
    // （在某些编译器中可能需要特定的编译选项），或者使用调试工具来观察实际发生的构造函数调用。

    cout << " ************************************** " << endl;
    vector<String> vec;
//    vec.push_back(s1);
    cout << "-------------------------" << endl;
    vec.push_back(String("bbb"));
//    vec.emplace_back("bbb");
    cout << " ************************************** " << endl;
    /*  String(const String&) 构造临时对象
        String(const char *cstr) 你哦默认构造
        String(String&&)
        String(String&&)
        ~String()
        ~String()
        这里多发生了一次，这个和编译器的选项有关
        String(String&&)
        ~String()

        因此更建议用
        vec.emplace_back("bbb");
     * */

    return 0;
}