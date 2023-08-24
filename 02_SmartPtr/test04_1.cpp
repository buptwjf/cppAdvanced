//
// Created by 86188 on 2023/8/2.
//

#include <iostream>
#include <memory>
#include <thread>

using namespace std;

/*
    智能指针的删除器 deletor
    智能指针：能够保证资源绝对的释放 delete ptr;
    由于智能指针有可能还管理文件资源，因此需要自己定义 delete 操作
*/
/*
    unique_ptr shared_ptr 都带了删除器
    ~unique_ptr() { 是一个函数对象的调用 deletor(ptr);}
    template<typename T>
    class Deletor{
    public:
        void operator() (T *ptr){
            delete ptr;
        }
    }
 */

#include <functional>

// 使用 lambda 表达式 => 函数对象 function 简化
int main() {
    unique_ptr<int, function<void(int *) >>
            ptr1(new int[100], [](int *p) -> void {
        cout << "call lambda release new int[100]" << endl;
        delete[] p;
    });
    unique_ptr<std::FILE , function<void(std::FILE *) >>
            ptr2(fopen("data.text", "w"), [](FILE *p) -> void {
        cout << "call lambda release data.text" << endl;
        fclose(p);
    });
    return 0;
}