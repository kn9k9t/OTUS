#pragma once
//-----------------------------------------------
#include "CommonTypes.h"
#include <iostream>
#include <fstream>
//-----------------------------------------------
class Printer
{
public:
  void onNewData()
  {
    _dataStartPoint = std::chrono::system_clock::now();
  }

  void print(const VecString & data)
  {
    auto printData = [](auto & os, const VecString & data)
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
      os << std::endl;
    };

    if (data.empty())
      return;
    std::string logName("bulk-");
    const auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(_dataStartPoint.time_since_epoch()).count();
    logName.append(std::to_string(timeSinceEpoch));
    logName.append(".log");
    std::ofstream log(logName);

    printData(std::cout, data);
    printData(log, data);
  }

private:
  TimePoint _dataStartPoint;
};
//-----------------------------------------------
