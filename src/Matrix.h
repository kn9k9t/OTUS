#pragma once
//-----------------------------------------------
#include <map>
//-----------------------------------------------
template <typename Value, Value defaultValue>
class Matrix
{
  using Coordinate = std::pair<int, int>;
  using MatrixVal = Matrix<Value, defaultValue>;

  class MatrixElement
  {
    MatrixVal & _matrix;
  public:
    MatrixElement(MatrixVal & matrix): _matrix(matrix) {};
    auto & operator=(const Value & other)
    {
      if(other == defaultValue)
        _matrix._data.erase(_matrix._coordinate);
      else
        _matrix._data[_matrix._coordinate] = other;
      return *this;
    }
    operator Value()
    {
      const auto it = _matrix._data.find(_matrix._coordinate);
      return it == _matrix._data.end() ? defaultValue : it->second;
    }
  };

  class MatrixRow
  {
    MatrixVal & _matrix;
  public:
    MatrixRow(Matrix<Value, defaultValue> & matrix): _matrix(matrix) {};
    auto operator[](const int columNum)
    {
      _matrix._coordinate.second = columNum;
      return _matrix._element;
    }
  };


  std::map<Coordinate, Value> _data;
  MatrixRow               _row;
  MatrixElement           _element;
  std::pair<int, int>     _coordinate;

  public:
    Matrix(): _row(*this), _element(*this){};

    auto & operator[](const int rowNum)
    {
      _coordinate.first = rowNum;
      return this->_row;
    }

    auto begin() { return std::begin(_data); }
    auto end() { return std::end(_data); }
    std::size_t size() { return _data.size(); }
};
