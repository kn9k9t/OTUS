#pragma once
//-----------------------------------------------
#include <vector>
#include <string>
#include <chrono>
//-----------------------------------------------
typedef std::vector<std::string> VecString;
typedef std::chrono::system_clock::time_point TimePoint;
//-----------------------------------------------
template <typename Stream>
void printBulk(Stream & os, const VecString & data)
{
  if (data.empty())
  {
    os << "Data is empty";
    return;
  }
  os << "bulk: ";

  auto last = std::prev(data.end());
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    if (it != last)
      os << *it << ",";
    else
      os << *it;
  }
  os << '\n';
};
//-----------------------------------------------
