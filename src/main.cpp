#include <iostream>
#include <fstream>
#include "IPv4.h"
//-----------------------------------------------
bool readIPs(VecIPv4 & ips)
{
  try
  {
    for (std::string line; std::getline(std::cin, line);)
    {
      size_t tabPos = line.find('\t');
      if (tabPos == std::string::npos)
      {
        std::cout << "Wrong line format, tabulation absent in line: " << line << '\n';
        return false;
      }
      IPv4 ip;
      ip.fill(line.substr(0, tabPos));
      ips.push_back(ip);
    }
  }
  catch (std::exception & ex)
  {
    std::cout << ex.what();
    return false;
  }
  return true;
}
//-----------------------------------------------
int main()
{
  VecIPv4 ips;
  readIPs(ips);
  sortDescending(ips);
  print(ips);
  print(getFilteredStrict(ips, std::array<int, 4>({1, -1, -1, -1})));
  print(getFilteredStrict(ips, std::array<int, 4>({46, 70, -1, -1})));
  print(getFilteredAny(ips, std::array<int, 4>({46, 46, 46, 46})));
}
//-----------------------------------------------
