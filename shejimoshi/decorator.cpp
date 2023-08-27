//
// Created by 86188 on 2023/8/27.
//

#include <iostream>

using namespace std;

/*
 * 装饰器：主要是增加现有类的功能，但是增加现有类的功能，还有一个方法，就是新增加一个子类 ，但是会导致产生更多的继承子类
 *
 * */

class Car {
public:
    virtual void show() = 0;
};

class Bmw : public Car {
public:

    void show() {
        cout << "Basic Bmw car ->" << endl;
    }
};

class Audi : public Car {
public:

    void show() {
        cout << "Basic Audi car ->" << endl;
    }
};

// #1 装饰器类
class CarDecorator01 : public Car {
public:
    CarDecorator01(Car *p) : pCar(p) {}

    void show() {
        pCar->show();
        cout << " < ABS > ";
    }

private:
    Car *pCar;
};


// #1 装饰器类
class CarDecorator02 : public Car {
public:
    CarDecorator02(Car *p) : pCar(p) {} // #2 装饰器的构造函数必须有个 基本功能

    void show() {
        pCar->show();
        cout << " < Lidar > ";
    }

private:
    Car *pCar;
};

int main() {
    Car *p1 = new CarDecorator01(new Bmw());  // #3 用装饰器对象对基本对象进行装饰
    p1->show();
    cout << endl;
    Car *p2 = new CarDecorator02(p1); // #4 可以反复装饰
    p2->show();
    return 0;
}