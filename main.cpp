#include <map>
#include "lib.hpp"
#include "custom_container.hpp"
#include "profile.hpp"

int main() {
    {
        LOG_DURATION("Map with default std::allocator")
        std::map<int, int> m1;
        for (int i = 0; i < 10; ++i)
            m1[i] = factorial(i);

        for (auto const& pair : m1){
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    {
        LOG_DURATION("Map with custom allocator")
        std::map<int, int, std::less<>, custom_allocator<std::pair<const int, int>, 10>> m2;
        std::cout<< m2.size() << std::endl;
        for (int i = 0; i < 10; ++i)
            m2[i] = factorial(i);

        for (auto const& pair : m2){
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }


//    custom_vector<int, std::allocator<int>> v;
//    for (int i = 0; i < 10; i++){
//        v.push_back(i);
//    }

    return 0;
}