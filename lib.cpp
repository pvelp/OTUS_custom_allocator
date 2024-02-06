#include "lib.hpp"
#include <map>
#include <iostream>

int factorial(const int& value){
    int res = 1;
    for (int i = 1; i < value+1; i++){
        res *= i;
    }
    return res;
}