//-----------------------------------------------
#include "CmdMng.h"
#include <iostream>
//-----------------------------------------------
int getBulkSize(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cout << "Error: incorrect arguments count" << std::endl;
    return -1;
  }

  return atoi(argv[1]);
}
//-----------------------------------------------
int main(int argc, char ** argv)
{
  int bulkSize = getBulkSize(argc, argv);
  CmdMng mng(bulkSize);
  for (std::string cmd; std::getline(std::cin, cmd);)
  {
    mng.addNewCmd(std::move(cmd));
  }

  return 0;
}
//-----------------------------------------------
