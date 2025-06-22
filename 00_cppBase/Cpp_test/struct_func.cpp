//
// Created by 86188 on 2023/9/27.
//
#include <iostream>

struct Shape {
    double (*area)(const Shape*); // 函数指针，用于计算面积
};

struct Rectangle {
    Shape base; // 基类
    double width;
    double height;
};

double calculateRectangleArea(const Shape* shape) {
    const Rectangle* rect = (const Rectangle*)shape;
    return rect->width * rect->height;
}

struct Circle {
    Shape base; // 基类
    double radius;
};

double calculateCircleArea(const Shape* shape) {
    const Circle* circle = (const Circle*)shape;
    return 3.14159265358979323846 * circle->radius * circle->radius;
}

void initializeRectangle(Rectangle* rect, double width, double height) {
    rect->base.area = calculateRectangleArea;
    rect->width = width;
    rect->height = height;
}

void initializeCircle(Circle* circle, double radius) {
    circle->base.area = calculateCircleArea;
    circle->radius = radius;
}

double getArea(const Shape* shape) {
    return shape->area(shape);
}

int main() {
    Rectangle rect;
    Circle circle;

    initializeRectangle(&rect, 5.0, 4.0);
    initializeCircle(&circle, 3.0);

    std::cout << "Rectangle Area: " << getArea(&rect) << std::endl;
    std::cout << "Circle Area: " << getArea(&circle) << std::endl;

    return 0;
}
