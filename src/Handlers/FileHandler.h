#pragma once
//-----------------------------------------------
#include "CommonTypes.h"
#include "IHandler.h"
#include <fstream>
//-----------------------------------------------
class FileHandler : public IHandler
{
public:
  virtual ~FileHandler() = default;

  void handle(const VecString & data) override
  {
    if (data.empty())
      return;

    std::string fileName("bulk-");
    const auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(_dataStartPoint.time_since_epoch()).count();
    fileName.append(std::to_string(timeSinceEpoch));
    fileName.append(".log");
    std::ofstream fileStream(fileName);

    printBulk(fileStream, data);
  }

  void onNewBulkStarted() override
  {
    _dataStartPoint = std::chrono::system_clock::now();
  }

private:
  TimePoint _dataStartPoint;
};
//-----------------------------------------------
