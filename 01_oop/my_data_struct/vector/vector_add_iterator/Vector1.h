//
// Created by 86188 on 2023/12/25.
//

#ifndef CPPADVANCED_VECTOR1_H
#define CPPADVANCED_VECTOR1_H
//
// Created by 86188 on 2023/11/15.
//
/*
 * 在之前基础 base_vector 的基础上，增加 allocator
 * allocator 应该做四件事
 * 1. 内存开辟，内存释放
 * 2. 对象构造，对象析构
 * */

#include <stdexcept> // 包含 std::out_of_range 所需的头文件
#include <iostream>

// 对 Vector 的 iterator 迭代器功能进行完善
// 增加 insert 和 erase 功能，在迭代器失效的时候更新迭代器

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

template<typename T, typename Alloc = Allocator<T >> // 指定默认的分配器
class Vector {
public:
// 默认构造
    explicit Vector(int size = 2, const Alloc &alloc = Alloc()) : _allocator(alloc), _head(nullptr, nullptr) {
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
    [[nodiscard]]bool empty() const { return _first == _last; };
    [[nodiscard]]int size() const { return _last - _first; };
    [[nodiscard]]int capacity() const { return _end - _first; };

    class iterator {
    public:
        friend class Vector<T, Alloc>;

        // 修改 iterator 的构造函数
        iterator(T *ptr = nullptr, Vector<T, Alloc> *pVec = nullptr) : _ptr(ptr), _pVec(pVec) {
            // 每定义一个 iterator，就在链表上进行头插法插入一个 Iterator_Base
            if (_pVec != nullptr) {
                Iterator_Base *it = new Iterator_Base(this, _pVec->_head._next);
                _pVec->_head._next = it;
            } else {
                std::cout << "_pVec = nullptr" << std::endl;
            }
        }

        bool operator!=(const iterator &it) {
            // 需要判断迭代器 所在的容器是否一样
            if (_pVec == nullptr || _pVec != it._pVec) {
                throw std::runtime_error("iterator incompatible!");
            }
            return _ptr != it._ptr;
        }

        iterator operator++() {
            // 需要判断迭代器是否有效
            if (!_pVec) {
                throw std::runtime_error("iterator invalid!");
            }
            ++_ptr;
            return *this;
        }

        T operator*() {
            // 需要判断迭代器是否有效
            if (!_pVec) {
                throw std::runtime_error("iterator invalid!");
            }
            return *_ptr;
        }

    private:
        T *_ptr;
        // Iterator 增加指向当前容器的指针
        Vector<T, Alloc> *_pVec;
    };

    iterator begin() { return {iterator(_first, this)}; };
    iterator end() { return {iterator(_last, this)}; }

// 判断迭代器是否有效
    void verify(T *first, T *last) {
        // 检查当前容器的迭代器，是否有在 [first, last] 范围中
        Iterator_Base *pre = &this->_head;
        Iterator_Base *it = this->_head._next;
        while (it) {
            if (it->_curIterator->_ptr >= first && it->_curIterator->_ptr <= last) {
                // 迭代器失效，将其 的容器指针置为空
                it->_curIterator->_pVec = nullptr;
                // 删除当前 Iterator_Base，继续遍历
                pre->_next = it->_next;
                delete it;
                it = pre->_next;
            } else {
                pre = it;
                it = it->_next;
            }
        }
    }

    // 自定义 vector 容器的 insert 方法
    iterator insert(iterator it, const T &val) {
/*
 *  1. 不考虑扩容 verify(_first-1, _last);
 *  2. 不考虑 it._ptr 指针的合法性
 * */
        verify(it._ptr, _last); // 防止从在一个位置上插入，此时所有迭代器都要失效
        T *p = _last;
        // 从最后一个元素的下一个位置，构造前一个元素 -> 将 _ptr 之后的每一个元素后移一位
        while (p > it._ptr) {
            _allocator.construct(p, *(p - 1));
            _allocator.destroy(p - 1);
            p--;
        }
        _allocator.construct(p, val);
        _last++;
        return iterator(p, this);
    }

    // 自定义 Vector 容器的 erase 方法
    iterator erase(iterator it) {
        verify(it._ptr, _last);
        T *p = it._ptr;

        while (p < _last - 1) {
            _allocator.destroy(p);
            _allocator.construct(p, *(p + 1));
            p++;
        }
        _allocator.destroy(p);
        _last--;
        return iterator(it._ptr, this);

    }
protected:
    [[nodiscard]]bool full() const { return _end == _last; };
    void expand(); // 扩容
private:
    T *_first; // 指向数组元素的起始位置
    T *_last; // 指向数组中有效元素的后继位置
    T *_end; // 指向数组空间的后继位置
    Alloc _allocator;

// 增加一个 iterator 的链表
// 定义 链表的节点 Iterator_Base
    struct Iterator_Base {
        Iterator_Base(iterator *c = nullptr, Iterator_Base *n = nullptr) : _curIterator(c), _next(n) {}

        iterator *_curIterator;
        Iterator_Base *_next;
    };

// 链表的头节点
    Iterator_Base _head;
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
        // 需要 verify
        verify(_last - 1, _last);
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
        _allocator.destroy(p); // 4. 析构容器元素
    }
    _allocator.deallocate(temp); // 5. 释放容器空间
    _end = _first + 3 * size;
    _last = _first + size;
}

#endif //CPPADVANCED_VECTOR2_H
