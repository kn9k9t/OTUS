#pragma once
//-----------------------------------------------
/*
 * @file PrintIp.h
 * @brief Overloaded Function to Print IP from integers, vec, list, string and tuple
 * */
//-----------------------------------------------
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <tuple>
#include <variant>
#include <type_traits>
//-----------------------------------------------
/*
 * @brief Print integral's bytes as IP
 * @param integral to print
 * */
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(T val)
{
  int size = sizeof(val);
  for (int i = 1; i < size; ++i)
  {
    std::cout << ((val >> ((size - i) * 8)) & 0xFF) << '.';
  }
  std::cout << (val & 0xFF) << std::endl;
}
//-----------------------------------------------
/*
 * @brief Print std::string as IP
 * @param string to print
 * */
template<typename T>
typename std::enable_if<std::is_same<std::string, T>::value>::type
print_ip(const T & val)
{
  std::cout << val << std::endl;
}
//-----------------------------------------------
/*
 * @brief Print std::vector or std::list as IP element by element with dot as separator
 * @param container to print
 * */
template<typename T>
typename std::enable_if<std::is_same<std::vector<typename T::value_type>, T>::value
                     || std::is_same<std::list<typename T::value_type>, T>::value>::type
print_ip(const T & val)
{
  auto last = std::prev(val.end());
  for (auto it = val.begin(); it != val.end(); ++it)
  {
    std::cout << *it;
    if (it != last)
      std::cout << '.';
  }
  std::cout << std::endl;
}
//-----------------------------------------------
/*
 * @brief Print std::tuple as IP element by element with dot as separator
 * Require all elements of tuple to be the same type
 * @param tuple to print
 * */
template<template <class ...>class T, typename ...Types>
typename std::enable_if<std::is_same<std::tuple<Types...>, class T<Types...>>::value>::type
print_ip(const T<Types...> & val)
{
  auto print_tuple = [](const auto & t, const auto & ...ts)
  {
    std::cout << std::forward<decltype(t)>(t);
    static_assert(std::conjunction_v<std::is_same<decltype(t), decltype(ts)>...>, "all tuple types must be the same");
    ((std::cout << '.' << std::forward<decltype(ts)>(ts)), ...);
  };

  std::apply(print_tuple, std::forward<decltype(val)>(val));
  std::cout << std::endl;
}
//-----------------------------------------------
