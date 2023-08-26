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
#include <mutex>

using namespace std;

#if 0

// 懒汉式单例设计模式是否是可重入的设计模式?线程是否安全
class Singleton {
public:
    // 是否是可重入函数？(线程安全？)
    static Singleton *getInstance() { // #3 获取类的唯一实例对象的接口方法
        if (instance == nullptr) { // 懒汉式实例模式的关键！
            /*
             * 1. 开辟内存
             * 2. 构造对象
             * 3. 给instance 赋值
             * a.假如线程1 进行到第二步，线程2又进来，这是后 instance 又为空，又开始构造对象,因此不是线程安全
             * */
            instance = new Singleton();
        }
        return instance;

    }

    // #4 将拷贝构造和拷贝赋值 delete
    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    static Singleton *instance; // #2 位于内存的数据段上只有一个指针
    Singleton() {} // #1 构造函数私有化
};

Singleton *Singleton::instance = nullptr;

# endif


#if 0
mutex mtx;

// 线程安全的懒汉式单例模式  使用互斥锁
class Singleton {
public:
    // # 1
    static Singleton *getInstance() {
//        lock_guard<mutex> guard(mtx);   // 锁的粒度太大了，单线程的情况下也要加锁
        if (instance == nullptr) {
            lock_guard<mutex> guard(mtx);   // 需要做双重判断
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    // # 2
    static Singleton *volatile instance; // volatile 保证各个线程不会把 instance 重新拷贝
    Singleton() {}
};

Singleton *volatile Singleton::instance = nullptr;
#endif


// 线程安全的懒汉式单例模式  精简版本（不使用互斥锁）
class Singleton {
public:
    // # 1
    static Singleton *getInstance() {
        // 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令
        static Singleton instance; // # 1 第一次运行的时候才初始化 但无法保证多线程环境下被调用两次
        return &instance;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton() {}
};


int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    return 0;
}