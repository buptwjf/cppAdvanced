#include <iostream>

enum Color {
    RED,
    GREEN,
    BLUE	// 注意没有逗号
};

int main() {
    Color myColor = GREEN;

    if (myColor == GREEN) {
        std::cout << "The color is green." << std::endl;
    }

    return 0;
}