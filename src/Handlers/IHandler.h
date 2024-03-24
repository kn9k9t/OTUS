#pragma once
//-----------------------------------------------
#include "CommonTypes.h"
//-----------------------------------------------
class IHandler
{
public:
  virtual ~IHandler() = default;
  virtual void handle(const VecString & data) = 0;
  virtual void onNewBulkStarted() = 0;
};
//-----------------------------------------------
