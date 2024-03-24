//-----------------------------------------------
#include "CmdMng.h"
#include "FileHandler.h"
#include "TerminalHandler.h"
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
  if (bulkSize <= 0)
    return -1;

  auto fileHandler = std::make_shared<FileHandler>();
  auto terminalHandler = std::make_shared<TerminalHandler>();

  CmdMng mng(bulkSize);
  mng.attach(fileHandler);
  mng.attach(terminalHandler);

  for (std::string cmd; std::getline(std::cin, cmd);)
  {
    mng.addNewCmd(std::move(cmd));
  }

  return 0;
}
//-----------------------------------------------
