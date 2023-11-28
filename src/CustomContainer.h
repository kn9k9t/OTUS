#pragma once
//-----------------------------------------------
#include <memory>
//-----------------------------------------------
template <class T, class Allocator = std::allocator<T>>
class CustomContainer
{
public:
  CustomContainer()
  {
    auto * ptr = alloc.allocate(1);
    if (ptr)
      _data = ptr;
  }

  typedef const T * const_pointer;
  typedef const_pointer const_iterator;
  const_iterator begin() const { return _data; }
  const_iterator end()   const { return _data + _size; }

  size_t size() { return _size; }
  size_t capacity() { return _capacity; }
  bool empty() { return _size == 0; }

  void push_back(const T & val)
  {
    if (_size == _capacity)
    {
      _capacity = _capacity * 2 + 1;
      T* newData = alloc.allocate(_capacity);
      std::copy(_data, _data + _capacity, newData);
      std::swap(newData, _data);
      alloc.deallocate(newData, _capacity);
    }

    alloc.construct(_data + _size, val);
    ++_size;
  }


private:
  std::size_t _size = 0;
  std::size_t _capacity = 0;
  T * _data = nullptr;

  Allocator alloc;
};
//-----------------------------------------------
