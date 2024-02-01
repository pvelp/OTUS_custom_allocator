#include <iostream>
#include <map>
#include "lib.hpp"


int main() {
    std::vector<char, custom_allocator<char, 40>> v;
    std::cout << "--stage1: capacity: " << v.capacity() << std::endl << std::endl;
    for (char i = 0; i < 5; i++) {
        v.push_back(i);
        std::cout << "--insert: " << +i << ", capacity: " << v.capacity() << std::endl;
    }
    std::cout << "--size: " << v.size() << " capacity: " << v.capacity() << std::endl;
    for (const auto &a: v) {
        std::cout << +a << std::endl;
    }

    return 0;
}