#pragma once
//-----------------------------------------------
#include "CommonTypes.h"
#include <memory>
//-----------------------------------------------
class IBulk
{
public:
  virtual ~IBulk() = default;
  virtual void onBulkFilled(const VecString & data) = 0;
};
//-----------------------------------------------
class Bulk
{
public:
  Bulk(size_t size, IBulk & user);

  void add(std::string && data);
  VecString release();
  void useDynamicSize();
  bool isEmpty();
private:
  bool _ignoreCapacity;
  size_t _capacity;
  VecString _data;
  IBulk & _user;
};
//-----------------------------------------------
