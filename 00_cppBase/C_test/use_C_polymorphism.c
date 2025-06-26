//
// 使用 C 语言实现多态
//
#include <stdio.h>

// 使用 typedef 简化声明
typedef struct Animal{
    void (*speak) (struct Animal* animal);  // 函数指针
} Animal;


void speak(Animal* animal){
    printf("Any animal\n");
}

void initAnimal(Animal *animal){
    animal->speak = speak;
}

// 子结构体
typedef struct Dog{
    Animal base;    // 复合 父结构体 来实现 "继承"
} Dog;

void dogSpeak(Animal* dog){
    printf("Dog speak\n");
}

void initDog(Dog* dog){
    dog->base.speak = dogSpeak; // 绑定子函数
}

int main(){
    Animal anl;
    initAnimal(&anl);   // 绑定 animal
    anl.speak(&anl);

    Dog dog;
    initDog(&dog);
    // 使用父类的指针 指向子类对象
    Animal *animal2dog = (Animal*) &dog;
    // 实现多态
    printf("dog:\n");
    animal2dog->speak(animal2dog);
    return 0;
}