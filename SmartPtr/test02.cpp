//
// Created by 86188 on 2023/8/2.
//

#include <iostream>
#include <memory>

using namespace std;


class B;

class A {
public:
    A() { cout << "A()" << endl; }

    ~A() { cout << "~A()" << endl; };
    shared_ptr<B> _ptrb;
};

class B {
public:
    B() { cout << "B()" << endl; }

    ~B() { cout << "~B()" << endl; };

    shared_ptr<B> _ptra;
};

int main(){
    shared_ptr<A> pa(new A());
    shared_ptr<B> pb(new B());



}