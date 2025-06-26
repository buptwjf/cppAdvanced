//
// Created by 86188 on 2023/9/6.
//
#include <iostream>

int main() {
    int num = 1;
    std::cout << &num << std::endl;

    // 将int类型指针转换为char类型指针，取第一个字节
    char *ptr = reinterpret_cast<char *>(&num);
    // 让 std::cout 以十六进制地址的方式输出指针地址。否则会把 ptr 当作一个字节(一个字符)输出
    std::cout << (ptr) << std::endl;
    std::cout << static_cast<void *>(ptr) << std::endl;

    if (*ptr == 1) {
        // 假如 int 是 小端法 存储
        // int  32位 0x 0001  地址由 高向低
        // 不论是大端法还是小端法指针指向内存中的低地址，也就是 1 所在的地址
        // char 8 位 0x 1     指针指向 1
        std::cout << "Little-endian" << std::endl;
    } else {
        std::cout << "Big-endian" << std::endl;
    }
    return 0;
}
