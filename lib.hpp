#include <iostream>


template <typename T, size_t N>
class custom_allocator
{
public:
    using value_type = T;
    custom_allocator() noexcept;
    template <typename U, size_t S> custom_allocator(const custom_allocator<U, S>&) noexcept;
    T* allocate(size_t n);
    void deallocate(T* p, size_t n);

    template< typename U, size_t S = N>
    struct rebind
    {
        typedef custom_allocator<U, S> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
private:
    static constexpr size_t pool_size{N};
    size_t cur_pos;
    size_t elem_count;
    T* pool{nullptr};
};

template<typename T, size_t N>
inline custom_allocator<T, N>::custom_allocator() noexcept : cur_pos(0), elem_count(0){
    pool = static_cast<T*>(::operator new(pool_size * sizeof (T)));
}


template<typename T, size_t N>
template<typename U, size_t S>
custom_allocator<T, N>::custom_allocator(const custom_allocator<U, S> &a) noexcept {
    pool = a.pool;
}


template<typename T, size_t N>
T* custom_allocator<T, N>::allocate(size_t n) {
    if (cur_pos + n > pool_size){
        throw std::bad_alloc();
    }
    cur_pos = n;
    T* tmp = pool + cur_pos;
    std::cout << "!custom_allocator::allocate, allocated additional " << n * sizeof(T) << " bytes, there are "
    << (pool_size - cur_pos) * sizeof (T)<< " bytes left, total allocated: " << cur_pos * sizeof(T) << std::endl;
    return tmp;
}


template<typename T, size_t N>
void custom_allocator<T, N>::deallocate(T *p, size_t n) {
    std::cout << "custom_allocator::deallocate, " << "diff = " << p - pool << " n = " << n << std::endl << std::endl;
    if (!p) return;
    cur_pos -= n;
    if (cur_pos != 0) return;
    free(p);
    std::cout << "deallocated all mem" << std::endl;
}


template <typename T, size_t N, typename U, size_t S>
constexpr bool operator==(const custom_allocator<T, N>& a1, const custom_allocator<U, S>& a2)
{
    return a1.pool == a2.pool;
}


template <typename T, size_t N, typename U, size_t S>
constexpr bool operator!=(const custom_allocator<T, N>& a1, const custom_allocator<U, S>& a2){
    return a1.pool != a2.pool;
}
