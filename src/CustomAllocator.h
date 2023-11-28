#pragma once
//-----------------------------------------------
#include <memory>
#include <new>
//-----------------------------------------------
template <typename T>
struct CustomAllocator
{
public:
  typedef T value_type;

  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;

  size_t _size;
  static constexpr size_t _capacity = sizeof(T) * 1000;
  uint8_t _data[_capacity];

  CustomAllocator() = default;
  ~CustomAllocator() = default;
  template <typename V>
  CustomAllocator(const CustomAllocator<V> &) {}

  T * allocate(std::size_t n)
  {
    if (_size + n > _capacity)
      throw std::bad_alloc();
    int curSize = _size;
    _size += n;
    return reinterpret_cast<T *>(_data) + curSize;
  }

  void deallocate (T *, std::size_t) {}

  template <class Up, class... Args>
  void construct(Up* p, Args&&... args)
  {
    ::new ((void*)p) Up(std::forward<Args>(args)...);
  }

  void destroy(pointer ptr)
  {
    ptr->~T();
  }

  template <class U>
  struct rebind
  {
    typedef CustomAllocator<U> other;
  };
};
//-----------------------------------------------
template <class T, class U>
constexpr bool operator== (const CustomAllocator<T>&, const CustomAllocator<U>&) noexcept {
  return false;
}
//-----------------------------------------------
template <class T, class U>
constexpr bool operator!= (const CustomAllocator<T>&, const CustomAllocator<U>&) noexcept {
  return false;
}
//-----------------------------------------------
