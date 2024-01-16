//-----------------------------------------------
#include "Matrix.h"
#include <cassert>
#include <iostream>
//-----------------------------------------------
int main()
{
  Matrix<int, 0> matrix;
  for (int i = 0; i < 10; ++i)
    matrix[i][i] = i;

  for (int i = 9; i >= 0; --i)
    matrix[9 - i][i] = i;

  for (int i = 1; i < 9; ++i)
  {
    for (int k = 1; k < 9; ++k)
    {
      std::cout << matrix[i][k] << ' ';
    }
    std::cout << '\n';
  }

  std::cout << matrix.size() << std::endl;

  for (auto element : matrix)
  {
  int x = element.first.first;
  int y = element.first.second;
  int v = element.second;
  std::cout << x << ' ' << y  << ' ' << v << std::endl;
  }
}
//-----------------------------------------------
