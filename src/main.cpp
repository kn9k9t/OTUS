#include <iostream>
#include "Version/SoftwareVersion.h"
//-----------------------------------------------
//-----------------------------------------------
int main()
{
  std::cout << "Build: " << getSoftwareVersion() << "\n"
            << "Hello World!" << "\n";
  return 0;
}
//-----------------------------------------------
