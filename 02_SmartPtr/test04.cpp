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

template<typename T>
class MyDeletor {
public:
    void operator()(T *ptr) const {
        cout << "call MyDeletor !" << endl;
        delete[] ptr;
    }
};
template<typename T>
class MyFileDeletor {
public:
    void operator()(T *ptr) const {
        cout << "call MyFileDeletor !" << endl;
        fclose(ptr);
    }
};
int main() {
    unique_ptr<int, MyDeletor<int>> ptr1(new int[100]); // delete []ptr
    unique_ptr<FILE , MyFileDeletor<::FILE>> ptr2(fopen("data.txt", "w")); // delete []ptr
    return 0;
}