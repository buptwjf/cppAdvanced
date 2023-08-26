//
// Created by 86188 on 2023/8/26.
//
#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
 * 简单工厂 Simpler Factory : 把对象的创建封装在一个接口函数中，通过传入不同的标识返回创建的对象
 *      好处：客户自己不用自己负责 new
 *      坏处：提供创建对象实例的接口函数不闭合，不能对修改关闭
 *
 * 设计模式
 *      工厂方法 Factory Method
 *      Factory 基类，提供另一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的产品，可以做到不同的产品在不同的
 *      工厂里面创建，能够对现有工厂，以及产品的关闭
 *
 *      实际上，很多产品是有关联关系的，属于同一个产品簇，不应该放在不同的工厂里面创建，这样不符合实际产品对象创建逻辑，二是工厂类
 *      太多了，不好维护。
 *
 *      抽象工厂 Abstract Factory
 *      把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面 AbstractFactory，派生类（具体产品的工厂），
 *      应该负责该产品簇里所有的产品
 *
 * 要工厂模式：主要是封装了对象的创建
 * */
class Car {
public:
    Car(string name) : _name(name) {}

    virtual void show() = 0;

protected:
    string _name;
};

class Bmw : public Car {
public:
    Bmw(string name) : Car(name) {} // !!

    void show() {
        cout << "Bmw car ->" << _name << endl;
    }
};

class Audi : public Car {
public:
    Audi(string name) : Car(name) {}

    void show() {
        cout << "Audi car ->" << _name << endl;
    }
};

enum CarType {
    BMW, AUDI
};

#if 0
// 简单工厂模式
/*
 * 问题：简单工厂不符合开闭原则
 * */
class SimpleFactory {
public:
    Car *creatCar(CarType ct) {
        switch (ct) {
            case BMW:
                return new Bmw("X1");
            case AUDI:
                return new Audi("A6");
            default:
                cout << "error" << endl;
        }
        return nullptr;

    }
};

int main() {
    Car *p1 = new Bmw("X1");
    Car *p2 = new Audi("A6");

//    Car *p3 = factory->creatCar(BMW);
//    Car *p4 = factory->creatCar(AUDI);

    // 使用智能指针封装
    unique_ptr<SimpleFactory>factory (new SimpleFactory());
    unique_ptr<Car> p3(factory->creatCar((BMW)));
    unique_ptr<Car> p4(factory->creatCar((AUDI)));
    p3->show();
    p4->show();
    return 0;
}
#endif

// 工厂方法

// 工厂的基类
class Factory {
public:
    virtual Car *createrCar(string name) = 0;
};


// 具体各个品牌的工厂
// 宝马工厂
class BMWFactory : public Factory {
public:
    Car *createrCar(string name) {
        return new Bmw(name);
    }
};

// 奥迪工厂
class AudiFactory : public Factory {
public:
    Car *createrCar(string name) {
        return new Audi(name);
    }
};

/*
 * 如果要实现 奔驰类
 * 只要定义 class Benz , 和 class Benzfactory
 * */
int main() {
    unique_ptr<Factory> bmwfty(new BMWFactory());
    unique_ptr<Factory> audifty(new AudiFactory());
    unique_ptr<Car> p1(bmwfty->createrCar("X1"));
    unique_ptr<Car> p2(audifty->createrCar("A6"));
    p1->show();
    p2->show();

}