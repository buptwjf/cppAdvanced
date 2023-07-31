//
// Created by 86188 on 2023/7/31.
//

#include "iostream"
template<class Key>
struct hash{};

template<>
struct hash<char>{
    size_t operator() (char x) const {return x;};
};
template<>
struct hash<int>{
    size_t operator() (int x) const {return x;};
};
template<>
struct hash<long>{
    size_t operator() (long x) const {
        std::cout << "use long" << std::endl;
        return x;
    }
};

int main(){
    std::cout << hash<long>()(1000);
    return 0;
}