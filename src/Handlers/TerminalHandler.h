#pragma once
//-----------------------------------------------
#include "CommonTypes.h"
#include "IHandler.h"
#include <iostream>
//-----------------------------------------------
class TerminalHandler : public IHandler
{
public:
  virtual ~TerminalHandler() = default;

  void handle(const VecString & data) override
  {
    if (data.empty())
      return;
    printBulk(std::cout, data);
  }

  void onNewBulkStarted() override {}
};
//-----------------------------------------------
