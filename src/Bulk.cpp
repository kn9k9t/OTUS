#include "Bulk.h"
//-----------------------------------------------
Bulk::Bulk(size_t size, IBulk & user) :
  _ignoreCapacity(false),
  _capacity(size),
  _user(user) {}
//-----------------------------------------------
void Bulk::add(std::string && data)
{
  _data.push_back(data);
  if (!_ignoreCapacity && _data.size() >= _capacity)
  {
    _user.onBulkFilled(std::move(_data));
    _data.clear();
  }
}
//-----------------------------------------------
VecString Bulk::release()
{
  VecString data = std::move(_data);
  _data.clear();
  _ignoreCapacity = false;
  return data;
}
//-----------------------------------------------
void Bulk::useDynamicSize() { _ignoreCapacity = true; }
//-----------------------------------------------
bool Bulk::isEmpty() { return _data.empty(); }
//-----------------------------------------------
