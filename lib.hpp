#pragma once

#include <iostream>

template<typename T, size_t ALLOC_SIZE>
class custom_allocator {
public:
    using value_type = T;

    custom_allocator() noexcept: pool_begin(static_cast<char *>(::operator new(ALLOC_SIZE * sizeof(T)))) {
        pool_end = pool_begin + ALLOC_SIZE * sizeof(T);
        pool_tail = pool_begin;
        pool_size = ALLOC_SIZE;
    }


    ~custom_allocator() { delete pool_begin; };


    template<typename U, size_t S>
    custom_allocator(const custom_allocator<U, S> &a) noexcept {
        pool_begin = a.pool_begin;
        pool_tail = a.pool_tail;
        pool_end = a.pool_end;
    }

    T *allocate(size_t n) {
        //        if (n != 1) throw std::logic_error("Can't allocate arrays");
        if (pool_tail + n * sizeof(T) > pool_end) throw std::bad_alloc();
//        if (pool_tail + n * sizeof(T) > pool_end){
//            size_t cur_pos = (pool_tail - pool_begin)/sizeof(T);
//            char* tmp = static_cast<char*>(::operator new((size_t)(ALLOC_SIZE*1.5)*sizeof(T)));
//
//            for (size_t i = 0; i < pool_size; i++){
//                tmp[i] = pool_begin[i];
//            }
//
//            pool_size = (size_t)(pool_size*1.5);
//            delete pool_begin;
//            pool_begin = tmp;
//            pool_end = pool_begin + pool_size*sizeof(T);
//            pool_tail = pool_begin + cur_pos + n;
//            return reinterpret_cast<T *>(pool_tail);
//        }
        auto result = reinterpret_cast<T *>(pool_tail);
        pool_tail += n * sizeof(T);
//        std::cout << "begin: " <<  (void*)pool_begin << " end: " << (void*)pool_end <<
//                  " current tail: " << (void*)pool_tail << " add: " << n * sizeof(T)<<
//                  " total added: " << pool_tail - pool_begin << std::endl;
        return result;
    }


    void deallocate(T *p, size_t n) {

    }


    template<typename U>
    struct rebind {
        using other = custom_allocator<U, ALLOC_SIZE>;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
private:
    char *pool_begin;
    char *pool_end;
    char *pool_tail;
    size_t pool_size;
};


template<typename T, size_t ALLOC_SIZE, typename U, size_t S>
constexpr bool operator==(const custom_allocator<T, ALLOC_SIZE> &a1, const custom_allocator<U, S> &a2) {
    return a1.pool == a2.pool;
}


template<typename T, size_t ALLOC_SIZE, typename U, size_t S>
constexpr bool operator!=(const custom_allocator<T, ALLOC_SIZE> &a1, const custom_allocator<U, S> &a2) {
    return a1.pool != a2.pool;
}


int factorial(const int &value);
