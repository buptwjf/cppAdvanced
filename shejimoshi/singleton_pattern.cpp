//
// Created by 86188 on 2023/8/25.
//
/*
 * 单例模式：一个类创建对象，不管创建多少次对象，永远只能得到该类型一个对象的实例
 *
 * 常用到的，比如日志模块，数据模块
 * 单例模式:
 * 饿汉式单例模式：还没有获取实例对象，实例对象就已经产生了
 * 懒汉式单例模式：唯一的实例对象，直到第一次获取它的时候，才产生
 * */
#include <iostream>

using namespace std;

// 饿汉式单例模式 一定是线程安全的，但是一开始就初始化对象会导致很麻烦
#if 0
class Singleton {
public:
    static Singleton *getInstance() { // #3 获取类的唯一实例对象的接口方法
        return &instance;
    }

    // #4 将拷贝构造和拷贝赋值 delete
    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    static Singleton instance; // #2 定义一个唯一的实例对象 位于内存的数据段

    Singleton() { // #1 构造函数私有化

    }

};

int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();


    return 0;
}
#endif


// 懒汉式单例设计模式是否是可重入的设计模式
class Singleton {
public:
    // 是否是可重入函数？(线程安全？)
    static Singleton *getInstance() { // #3 获取类的唯一实例对象的接口方法
        if (instance == nullptr) { // 懒汉式实例模式的关键！
            /*
             * 开辟内存
             * 构造对象
             * 给instance 赋值
             * */
            instance = new Singleton();
        } else {
            return instance;
        }
    }

    // #4 将拷贝构造和拷贝赋值 delete
    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    static Singleton *instance; // #2 位于内存的数据段上只有一个指针
    Singleton() {} // #1 构造函数私有化
};

Singleton *Singleton::instance = nullptr;


int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;


    return 0;
}