# oop 相关的代码说明

## my_data_struct

通过实现 complex 容器，String 和 Vector 学习 oop 和 STL 相关的知识

### 1. complex

* 实现 complex 类 ： 参考侯捷的版本
    - [x] 已复习一遍

### 2. string

* 实现 string 类：参考侯捷，施磊版本

#### base_string

1. myString.h : 侯捷版本的 string 容器
    - [x] 已复习一遍
2. myString1.h : 施磊版本的 string 容器
    - [x] 已复习一遍

    * 根据施磊的 oop 初级进行优化
    * a. 返回值优化
    * b. 增加 operator+ operator > < operator <<

### 3. vector

* 实现 vector 类

#### base_vector

1. Vector.h : 基础功能的 vector 容器
    - [x] 已复习一遍

#### vector_add_allocator

- [ ] 待复习

1. Vector.h : 增加分配器
2. Vector_base.h **base_vector 中的 Vector.h**

#### vector_add_iterator

- [ ] 待复习

1. Vector.h : 增加迭代器
2. Vector1.h : 避免迭代器失效

---

## oop

如何对一个对象进行优化

### 1. oop_object

- [x] 已复习一遍

1. oop_demo1.cpp

2. oop_demo2.cpp

3. oop_demo3.cpp

4. oop_demo4.cpp

### 2. ~~oop_string~~

以 String 类型为例子，增加右值引用的拷贝构造和拷贝赋值函数，来减少对象的构造次数

1. myString2.h

    - [x] 已复习一遍

    * 在 myString1.h 的基础上增加右值引用的拷贝构造和拷贝赋值函数
    * 使用 test_String.cpp 进行测试

2. Vector1.h
    - [ ] 待复习

    * move 和 forword 的使用

---
