#pragma once
//-----------------------------------------------
#include <string>
#include "Bulk.h"
#include "Printer.h"
//-----------------------------------------------
class CmdMng : public IBulk
{
public:
  CmdMng(int bulkSize);
  ~CmdMng();
  void addNewCmd(std::string && cmd);
private:
  int _blockNestingDepth;
  Bulk _bulk;
  Printer _printer;

  //IBulk
  virtual void onBulkFilled(VecString && data) override;
};
//-----------------------------------------------
