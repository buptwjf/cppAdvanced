//
// Created by 86188 on 2023/8/27.
//

/*
 * 行为型模式：主要关注的是对象之间的通信
 * 观察者-监听者模式（发布-订阅模式）设计模式
 * 主要关注的是对象的一对多关系，也就是多个对象都依赖一个对象，当该对象的状态发生改变时，其他对象都能接收到相应的通知
 *
 * 一组数据（对象） => 曲线图、柱状图、圆饼图
 * 当数据对象改变时，对象1、对象2、对象3应该及时收到相应的通知
 *
 * Observer1 Observer2 Observer3
 * Subject(主题)
 * */

// 观察者抽象类(基类)
class Observer {
public:
    virtual void handle(int msgId) = 0;
};

class Observer1 : public Observer {
public:
    virtual void handle(int msgId) = 0;
};

class Observer2 : public Observer {
public:
    virtual void handle(int msgId) = 0;
};

class Observer3 : public Observer {
public:
    virtual void handle(int msgId) = 0;
};

int main() {
    return 0;
}