#include "CmdMng.h"
//-----------------------------------------------
#include <iostream>
//-----------------------------------------------
CmdMng::CmdMng(int bulkSize) : _blockNestingDepth(0), _bulk(bulkSize, *this) {}
//-----------------------------------------------
CmdMng::~CmdMng()
{
  if (_blockNestingDepth == 0)
    _printer.print(_bulk.release());
}
//-----------------------------------------------
void CmdMng::addNewCmd(std::string && cmd)
{
  if (cmd == "{")
  {
    if (_blockNestingDepth == 0)
      _printer.print(_bulk.release());
    ++_blockNestingDepth;
    _bulk.useDynamicSize();
    return;
  }

  if (cmd == "}")
  {
    --_blockNestingDepth;
    if (_blockNestingDepth <= 0 && _bulk.isEmpty() == false)
      _printer.print(_bulk.release());
    return;
  }

  if (_bulk.isEmpty())
    _printer.onNewData();
  _bulk.add(std::move(cmd));
}
//-----------------------------------------------
void CmdMng::onBulkFilled(VecString && data)
{
  _printer.print(std::move(data));
}
//-----------------------------------------------
