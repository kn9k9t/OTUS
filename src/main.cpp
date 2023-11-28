#include <iostream>
#include <map>
#include <vector>
#include "CustomAllocator.h"
#include "CustomContainer.h"
//-----------------------------------------------
unsigned int factorial(unsigned int n)
{
  if (n == 0)
    return 1;
  return n * factorial(n - 1);
}
//-----------------------------------------------
template <typename T>
void printMap(const T & map)
{
  for (auto & val : map)
  {
    std::cout << val.first << " " << val.second << std::endl;
  }
  std::cout << std::endl;
}
//-----------------------------------------------
template <typename T>
void printVec(const T & container)
{
  for (auto & val : container)
  {
    std::cout << val << std::endl;
  }
  std::cout << std::endl;
}
//-----------------------------------------------
int main()
{
  std::map<int, int> firstMap;
  for (int i = 0; i < 10; ++i)
  {
    firstMap.emplace(i, factorial(i));
  }

  std::map<int, int, std::less<int>, CustomAllocator<std::pair<int, int>>> secondMap;
  for (int i = 0; i < 10; ++i)
  {
    secondMap.emplace(i, factorial(i));
  }

  CustomContainer<int> firstCustom;
  for (int i = 0; i < 10; ++i)
  {
    firstCustom.push_back(i);
  }

  CustomContainer<int, CustomAllocator<int>> secondCustom;
  for (int i = 0; i < 10; ++i)
  {
    secondCustom.push_back(i);
  }

  printMap(firstMap);
  printMap(secondMap);
  printVec(firstCustom);
  printVec(secondCustom);
}
//-----------------------------------------------
