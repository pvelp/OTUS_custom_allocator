#pragma once

#include <iostream>

template<class T, class Alloc>
class custom_vector {
public:
    custom_vector() = default;

    explicit custom_vector(size_t size) : data(std::allocator_traits<T>::allocate(alloc, size)),
                                          size_(0),
                                          capacity_(size) {}

//    ~custom_vector() { std::allocator_traits<T>::destroy(alloc, data); };

    T &operator[](size_t index) { return data[index]; };

    T *begin() { return data; };

    T *end() { return data + size_; };

    const T *begin() const { return data; };

    const T *end() const { return data + size_; };

    size_t size() { return size_; }

    size_t capacity() { return capacity_; };

    void push_back(const T &value){
        if (size_ == capacity_){
            if (capacity_ == 0){
                capacity_ = 1;
            } else {
                capacity_ = 2 * capacity_;
            }

            T* tmp = std::allocator_traits<T>::(alloc, capacity_);
            for (size_t i = 0; i < size_; i++) {
                tmp[i] = data[i];
            }

            std::allocator_traits<T>::destroy(alloc, data);
            data = tmp;


//            std::copy(data, data + capacity_ * sizeof(T), tmp);
//            std::swap(tmp, data);
//            std::allocator_traits<T>::deallocate(alloc, data, capacity_);
        }
        data[size_] = value;
        size_++;
    };

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T *data = nullptr;

    Alloc alloc;
};