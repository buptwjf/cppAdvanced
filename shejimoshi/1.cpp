//
// Created by 86188 on 2023/8/26.
//
#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
 *      抽象工厂 Abstract Factory
 *      把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面 AbstractFactory，派生类（具体产品的工厂），
 *      应该负责该产品簇里所有的产品
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

class CarLight {
    virtual void show() = 0;
};

class BmwLight : public CarLight {
public:
    void show() {
        cout << "Bmw light " << endl;
    }
};

class AudiLight : public CarLight {
public:
    void show() {
        cout << "Audi light " << endl;
    }
};
// 工厂方法

// 工厂的基类
class AbstractFactory {
public:
    virtual Car *createrCar(string name) = 0;

    virtual CarLight *createrLight() = 0;
};


// 具体各个品牌的工厂
// 宝马工厂
class BMWFactory : public AbstractFactory {
public:
    Car *createrCar(string name) {
        return new Bmw(name);
    }

    CarLight *createrLight() {
        return new BmwLight();
    }
};

// 奥迪工厂
class AudiFactory : public AbstractFactory {
public:
    Car *createrCar(string name) {
        return new Audi(name);
    }

    CarLight *createrLight() {
        return new AudiLight();
    }
};

/*
 * 如果要实现 奔驰类
 * 只要定义 class Benz , 和 class Benzfactory
 * */
int main() {
    unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
    unique_ptr<AbstractFactory> audifty(new AudiFactory());
    unique_ptr<Car> p1(bmwfty->createrCar("X1"));
    unique_ptr<Car> p2(audifty->createrCar("A6"));
    unique_ptr<CarLight> p4(bmwfty->createrLight());
    unique_ptr<CarLight> p5(audifty->createrLight());

    p1->show();
    p2->show();
    

}