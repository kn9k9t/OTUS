#pragma once
//-----------------------------------------------
#include <iostream>
#include <string>
#include "Bulk.h"
#include "IHandler.h"
//-----------------------------------------------
typedef std::shared_ptr<IHandler> ObserverPtr;
typedef std::weak_ptr<IHandler> ObserverWeakPtr;
typedef std::vector<ObserverWeakPtr> Observers;
//-----------------------------------------------
class CmdMng : public IBulk
{
public:
  CmdMng(int bulkSize);
  ~CmdMng();
  void addNewCmd(std::string && cmd);
  void attach(ObserverWeakPtr && observer);
private:
  int       _blockNestingDepth;
  Bulk      _bulk;
  Observers _observers;

  void releaseBulk();
  void handleBulk(const VecString & data);
  void onNewBulkStarted();
  template <typename Func>
  void forAllObservers(const Func & f)
  {
    for (auto it = _observers.begin(); it != _observers.end();)
    {
      if (auto locked = it->lock())
      {
        f(locked);
        ++it;
      }
      else
      {
        it = _observers.erase(it);
      }
    }
  }

  //IBulk
  virtual void onBulkFilled(const VecString & data) override;
};
//-----------------------------------------------
