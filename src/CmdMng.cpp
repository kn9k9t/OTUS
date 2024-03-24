#include "CmdMng.h"
//-----------------------------------------------
#include <iostream>
//-----------------------------------------------
CmdMng::CmdMng(int bulkSize) : _blockNestingDepth(0), _bulk(bulkSize, *this) {}
//-----------------------------------------------
CmdMng::~CmdMng()
{
  if (_blockNestingDepth == 0)
    releaseBulk();
}
//-----------------------------------------------
void CmdMng::addNewCmd(std::string && cmd)
{
  if (cmd == "{")
  {
    if (_blockNestingDepth == 0)
      releaseBulk();
    ++_blockNestingDepth;
    _bulk.useDynamicSize();
    return;
  }

  if (cmd == "}")
  {
    --_blockNestingDepth;
    if (_blockNestingDepth <= 0 && _bulk.isEmpty() == false)
      releaseBulk();
    return;
  }

  if (_bulk.isEmpty())
    onNewBulkStarted();
  _bulk.add(std::move(cmd));
}
//-----------------------------------------------
void CmdMng::attach(ObserverWeakPtr && observer)
{
  _observers.push_back(std::move(observer));
}
//-----------------------------------------------
void CmdMng::releaseBulk()
{
  const auto data = _bulk.release();
  forAllObservers([&](ObserverPtr observer)
  {
    observer->handle(data);
  });
}
//-----------------------------------------------
void CmdMng::handleBulk(const VecString & data)
{
  forAllObservers([&](ObserverPtr observer)
  {
    observer->handle(data);
  });
}
//-----------------------------------------------
void CmdMng::onNewBulkStarted()
{
  forAllObservers([&](ObserverPtr observer)
  {
    observer->onNewBulkStarted();
  });
}
//-----------------------------------------------
void CmdMng::onBulkFilled(const VecString & data)
{
  handleBulk(data);
}
//-----------------------------------------------
