//
// Created by 86188 on 2023/9/6.
//
#include <iostream>

int main() {
    int num = 1;
    std::cout << &num << std::endl;

    // 将int类型指针转换为char类型指针，取第一个字节
    char *ptr = reinterpret_cast<char *>(&num);
    std::cout << static_cast<void *>(ptr) << std::endl;

    if (*ptr == 1) {
        std::cout << "Little-endian" << std::endl;
    } else {
        std::cout << "Big-endian" << std::endl;
    }
    return 0;
}
