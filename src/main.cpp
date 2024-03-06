//-----------------------------------------------
#include "Hash.h"
#include "Settings.h"
#include "Scaner.h"
#include <iostream>
//-----------------------------------------------
int main(int argc, char ** argv)
{
  Settings settings;
  if (settings.fillFromArgs(argc, argv) == false)
    return 1;
  std::cout << settings;

  Scaner scaner(settings);
  scaner.scan();
  scaner.printDuplicates();
}
//-----------------------------------------------
