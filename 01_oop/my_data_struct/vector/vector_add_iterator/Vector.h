//
// Created by 86188 on 2023/11/15.
//
/*
 * 在之前基础 base_vector 的基础上，增加 allocator
 * allocator 应该做四件事
 * 1. 内存开辟，内存释放
 * 2. 对象构造，对象析构
 * */
#ifndef CPPADVANCED_VECTOR_H
#define CPPADVANCED_VECTOR_H

#include <stdexcept> // 包含 std::out_of_range 所需的头文件
#include <iostream>

// 对 Vector 增加 iterator 迭代器功能

template<typename T>
struct Allocator {
public:
    T *allocate(size_t size) { // 负责开辟内存
        return (T *) malloc(sizeof(T) * size);
    }

    void deallocate(void *p) { // 负责释放内存
        free(p);
    }

    void construct(T *p, const T &val) { // 构造对象
        new(p) T(val); // 在指定位置 new
    }

    void destroy(T *p) { // 负责析构对象
        p->~T();
    }

};

template<typename T, typename Alloc = Allocator<T>> // 指定默认的分配器
class Vector {
public:
    // 默认构造
    Vector(int size = 2, const Alloc &alloc = Alloc()) : _allocator(alloc) {
//    _first = new T[size]; 通过 allocator 开辟空间，而不是构造 size 个 T
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    // Vector 析构
    // 1. 析构对象 2. 释放 Vector 空间
    ~Vector() {
        while (_last != _first) {
            --_last;
            _allocator.destroy(_last);
        }
        _allocator.deallocate(_first); // 释放堆上的数组内存
        _first = _last = _end = nullptr;
        // 不能通过 _first 来释放内存，因为 Vector 不一定满
        // delete[] _first;
    }; // 析构

    // 拷贝构造函数
    // 1.allocate空间 2. construct 对象
    Vector(const Vector<T, Alloc> &vec) {
        int size = vec._end - vec._first;
        int len = vec._last - vec._first;
        // _first = new T[size];
        _first = _allocator.allocate(size);
        for (int i = 0; i < len; i++) {
            // _first[i] = vec[i];
            _allocator.construct(_first + i, vec[i]);
        }
        _last = _first + len;
        _end = _first + size;
    }

    // 拷贝赋值函数
    // 1. 析构容器元素 2. 释放容器空间 3. 申请新的空间 4. 构造容器元素
    Vector &operator=(const Vector<T, Alloc> &vec) {
        // 检查自赋值
        if (this != &vec) {
            int size = vec._end - vec._first; // 空间大小
            int len = vec._last - vec._first; // 元素多少
            for (T *p = _first; p != _last; ++p) {
                _allocator.destroy(p); // 析构元素
            }
            _allocator.deallocate(_first); // 释放空间

            _first = _allocator.allocate(size); // 分配空间
            // _first = new T[size];
            for (int i = 0; i < len; i++) {
                // _first[i] = vec[i];
                _allocator.construct(_first + i, vec[i]); // 构造元素
            }
            _last = _first + len;
            _end = _last + size;
            return *this;
        }
        return *this;
    }

    T &operator[](int index) const; // []
    void push_back(T elem);

    void pop_back();

    T &back() const;

    T &begin() const;

    [[nodiscard]] bool empty() const { return _first == _last; };

    [[nodiscard]] int size() const { return _last - _first; };

    [[nodiscard]] int capacity() const { return _end - _first; };

    // 1. 嵌套写法
    class iterator {
    public:
        iterator(T *ptr = nullptr) : _ptr(ptr) {}

        // 3. !=
        bool operator!=(const iterator &it) { return _ptr != it._ptr; }

        // 4. ++
        iterator operator++() {
            ++_ptr;
            return *this;
        }

        // 5. *
        T& operator*() { return *_ptr; }

    private:
        T *_ptr;
    };

    // 2. 增加 begin 和 end 方法
    iterator begin() { return {_first}; };

    iterator end() { return {_last}; }

protected:

    [[nodiscard]] bool full() const { return _end == _last; };

    void expand(); // 扩容
private:
    T *_first; // 指向数组元素的起始位置
    T *_last; // 指向数组中有效元素的后继位置
    T *_end; // 指向数组空间的后继位置
    Alloc _allocator;
};

// 注意判断 index 的合法性
template<typename T, typename Alloc>
inline T &Vector<T, Alloc>::operator[](const int index) const {
    int size = _last - _first;
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return *(_first + index);
}

// 注意判断是否需要扩容
template<typename T, typename Alloc>
inline void Vector<T, Alloc>::push_back(T elem) {
    if (full()) {
        expand();
    }
    _allocator.construct(_last++, elem); // 通过 allocator 构造元素
}

// 注意判断容器是否为空
template<typename T, typename Alloc>
inline void Vector<T, Alloc>::pop_back() {
    if (!this->empty()) {
        _allocator.destroy(--_last); // 通过 allocator 析构元素
    } else {
        throw std::out_of_range("empty!");
    }
}

// 注意判断容器是否为空
template<typename T, typename Alloc>
T &Vector<T, Alloc>::begin() const {
    if (!this->empty()) {
        return *_first;
    } else {
        throw std::out_of_range("empty!");
    }
}

// 注意判断是否为空
template<typename T, typename Alloc>
inline T &Vector<T, Alloc>::back() const {
    if (!this->empty()) {
        return *(_last - 1);
    } else {
        throw std::out_of_range("empty!");
    }
}

// 使用分配器进行扩容
// 3. 析构容器元素 4. 释放容器空间 1. 申请新的空间 2. 构造容器元素
template<typename T, typename Alloc>
inline void Vector<T, Alloc>::expand() {
    std::cout << "expand()" << std::endl;
    int size = _end - _first; // 原始容量
    T *temp = _first;
    _first = _allocator.allocate(2 * size); // 1. 申请新的空间
    for (int i = 0; i < size; i++) {
        _allocator.construct(_first + i, *(temp + i)); // 2. 构造容器元素
    }
    for (T *p = temp; p != _last; p++) {
        _allocator.destroy(p); // 3. 析构容器元素
    }
    _allocator.deallocate(temp); // 4. 释放容器空间
    _end = _first + 2 * size;
    _last = _first + size;
}

#endif //CPPADVANCED_VECTOR_H
