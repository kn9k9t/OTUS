#include <iostream>
#include <fstream>
#include "IPv4.h"
//-----------------------------------------------
const std::string l_pathToFileWithIPs = "../ip_filter.tsv";
//-----------------------------------------------
bool readIPs(VecIPv4 & ips)
{
  try
  {
    std::ifstream ipsFile;
    ipsFile.open(l_pathToFileWithIPs);
    if (ipsFile.is_open() == false)
    {
      std::cout << "Can't open file: " << l_pathToFileWithIPs;
      return false;
    }

    for (std::string line; std::getline(ipsFile, line);)
    {
      size_t tabPos = line.find('\t');
      if (tabPos == std::string::npos)
      {
        std::cout << "Wrong line format, tabulation absent in line: " << line;
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
  sort(ips);
  print(ips);
  print(getFilteredStrict(ips, std::array<int, 4>({1, -1, -1, -1})));
  print(getFilteredStrict(ips, std::array<int, 4>({46, 70, -1, -1})));
  print(getFilteredAny(ips, std::array<int, 4>({46, 46, 46, 46})));
}
//-----------------------------------------------
