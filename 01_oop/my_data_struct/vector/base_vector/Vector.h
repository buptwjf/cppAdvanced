//
// Created by 86188 on 2023/11/15.
//
/*
 * 实现一个向量容器
 * 1. 构造
 * 2. 析构
 * 3. 拷贝构造
 *      深拷贝
 * 4. 拷贝赋值
 *      左值引用
 *      右值引用
 * 5. 其他方法
 *  operator[]
 *  push_back; pop_back;
 *  back(); begin();
 *  full(); empty();
 *  size(); expand();
 * */
#ifndef CPPADVANCED_VECTOR_H
#define CPPADVANCED_VECTOR_H

#include <stdexcept> // 包含 std::out_of_range 所需的头文件

template<typename T>
class Vector {
public:
    explicit Vector(int size = 2); // 默认构造
    ~Vector(); // 析构
    Vector(const Vector<T> &vec); // 拷贝构造
    Vector &operator=(const Vector<T> &vec); // 拷贝复制
    T &operator[](int index) const; // []

    void push_back(T elem); // 在数组末尾插入元素
    void pop_back(); // 弹出数组末尾最后的元素

    T &back() const; // 返回数组最后的元素
    T &begin() const; // 返回数组开头元素

    [[nodiscard]] bool empty() const; // 判断数组是否为空
    [[nodiscard]] int size() const; // 输出数组中元素的数量
    [[nodiscard]] int capacity() const; // 输出数组的容量

protected:
    [[nodiscard]] bool full() const; // 判断数组是否内存已满
    void expand(); // 扩容

private:
    T *_first; // 指向数组元素的起始位置
    T *_last; // 指向数组中有效元素的后继位置
    T *_end; // 指向数组空间的后继位置
};

// 默认构造函数
template<typename T>
inline Vector<T>::Vector(int size) {
    _first = new T[size]; // 使用 new 开辟空间
    _last = _first;
    _end = _first + size;
}

// 析构函数
template<typename T>
inline Vector<T>::~Vector() {
    delete[] _first; // 注意要加 []
    _first = nullptr;
    _last = nullptr;
    _end = nullptr;
}

// 拷贝构造函数
template<typename T>
inline Vector<T>::Vector(const Vector<T> &vec) {
    int len = vec._last - vec._first;
    int size = vec._end - vec._first;
    _first = new T[size]; // 注意需要深拷贝，重新开辟内存
    for (int i = 0; i < len; i++) {
        _first[i] = vec[i];
    }
    _last = _first + len;
    _end = _last + size;
}

// 拷贝赋值函数
template<typename T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &vec) {
    // 注意：按引用传递；检查自赋值
    // if (_first != vec._first) { 不要通过起始指针来检查
    if (this != &vec) {
        delete[] _first; // 先释放内存
        int size = vec._end - vec._first;
        _first = new T[size];
        int len = vec._last - vec._first;
        for (int i = 0; i < len; i++) {
            *(_first + i) = *(vec._first + i);
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }
    return *this;
}

// 重载 operator[]
template<typename T>
inline T &Vector<T>::operator[](const int index) const {
    int size = _last - _first;
    // 注意判断 index 的合法性
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return *(_first + index);
}

// push_back
template<typename T>
inline void Vector<T>::push_back(T elem) {
    // 注意判断是否需要扩容
    if (full()) {
        expand();
    }
    *(_last++) = elem;
}

// pop_back
template<typename T>
inline void Vector<T>::pop_back() {
    // 注意判断容器是否为空
    if (!this->empty()) {
        --_last;
    } else {
        throw std::out_of_range("empty!");
    }
}

// 判断 Vector 是否为空
template<typename T>
bool Vector<T>::empty() const {
    return _first == _last;
}

// 输出初始元素
template<typename T>
T &Vector<T>::begin() const {
    // 注意判断容器是否为空
    if (!this->empty()) {
        return *_first;
    } else {
        throw std::out_of_range("empty!");
    }
}

// 输出末尾元素
template<typename T>
inline T &Vector<T>::back() const {
    // 注意判断是否为空
    if (!this->empty()) {
        return *(_last - 1);
    } else {
        throw std::out_of_range("empty!");
    }
}

// 输出容器中元素的数量
template<typename T>
int Vector<T>::size() const {
    return _last - _first;
}

// 输出容器的容量
template<typename T>
int Vector<T>::capacity() const {
    return _end - _first;
}

// 判断容器有没有满
template<typename T>
inline bool Vector<T>::full() const {
    return _end == _last;
}

// 扩容
template<typename T>
inline void Vector<T>::expand() {
    int size = _end - _first; // 原始容量
    T *temp = _first;
    // 注意二倍扩容，重新申请内存
    _first = new T[2 * size];
    for (int i = 0; i < size; i++) {
        *(_first + i) = *(temp + i);
    }
    delete[] temp;
    _end = _first + 2 * size;
    _last = _first + size;
}

#endif //CPPADVANCED_VECTOR_H
