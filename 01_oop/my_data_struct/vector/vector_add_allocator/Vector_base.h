//
// Created by 86188 on 2023/12/17.
//

#ifndef CPPADVANCED_VECTOR_BASE_H
#define CPPADVANCED_VECTOR_BASE_H

#include <stdexcept> // 包含 std::out_of_range 所需的头文件

template<typename T>
class Vector {
public:
    explicit Vector(int size = 2); // 默认构造
    ~Vector(); // 析构
    Vector(const Vector<T> &vec); // 拷贝构造
    Vector &operator=(const Vector<T> &vec); // 拷贝复制
    T &operator[](int index) const; // []
    void push_back(T elem);

    void pop_back();

    T &back() const;

    T &begin() const;

    [[nodiscard]] bool empty() const;

    [[nodiscard]] int size() const;

    [[nodiscard]] int capacity() const;

protected:
    [[nodiscard]] bool full() const;

    void expand(); // 扩容
private:
    T *_first; // 指向数组元素的起始位置
    T *_last; // 指向数组中有效元素的后继位置
    T *_end; // 指向数组空间的后继位置
};

// 注意应该预留空间
template<typename T>
inline Vector<T>::Vector(int size) {
    _first = new T[size];
    _last = _first;
    _end = _first + size;
}

// 注意要加 []
template<typename T>
inline Vector<T>::~Vector() {
    delete[] _first;
    _first = nullptr;
    _last = nullptr;
    _end = nullptr;
}

// 注意需要深拷贝，重新开辟内存
template<typename T>
inline Vector<T>::Vector(const Vector<T> &vec) {
    int len = vec._last - vec._first;
    int size = vec._end - vec._first;
    _first = new T[size];
    for (int i = 0; i < len; i++) {
        _first[i] = vec[i];
    }
    _last = _first + len;
    _end = _last + size;
}

// 注意：按引用传递；检查自赋值
template<typename T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &vec) {
    // 检查自赋值
//    if (_first != vec._first) { 不要通过起始指针来检查
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

// 注意判断 index 的合法性
template<typename T>
inline T &Vector<T>::operator[](const int index) const {
    int size = _last - _first;
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return *(_first + index);
}

// 注意判断是否需要扩容
template<typename T>
inline void Vector<T>::push_back(T elem) {
    if (full()) {
        expand();
    }
    *(_last++) = elem;
}

// 注意判断容器是否为空
template<typename T>
inline void Vector<T>::pop_back() {
    if (!this->empty()) {
        --_last;
    } else {
        throw std::out_of_range("empty!");
    }
}

template<typename T>
bool Vector<T>::empty() const {
    return _first == _last;
}

// 注意判断容器是否为空
template<typename T>
T &Vector<T>::begin() const {
    if (!this->empty()) {
        return *_first;
    } else {
        throw std::out_of_range("empty!");
    }
}

// 注意判断是否为空
template<typename T>
inline T &Vector<T>::back() const {
    if (!this->empty()) {
        return *(_last - 1);
    } else {
        throw std::out_of_range("empty!");
    }
}


template<typename T>
int Vector<T>::size() const {
    return _last - _first;
}

template<typename T>
int Vector<T>::capacity() const {
    return _end - _first;
}

template<typename T>
inline bool Vector<T>::full() const {
    return _end == _last;
}

// 注意二倍扩容
template<typename T>
inline void Vector<T>::expand() {
    int size = _end - _first; // 原始容量
    T *temp = _first;
    _first = new T[2 * size];
    for (int i = 0; i < size; i++) {
        *(_first + i) = *(temp + i);
    }
    delete[] temp;
    _end = _first + 2 * size;
    _last = _first + size;
}

#endif //CPPADVANCED_VECTOR_BASE_H
