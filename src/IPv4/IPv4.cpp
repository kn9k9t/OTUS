#include "IPv4.h"
#include <tuple>
#include <algorithm>
//-----------------------------------------------
bool IPv4::fill(const std::string & addr)
{
  auto splitStringBySeparator = [](const std::string & str, char separator)
  {
    std::vector<std::string> result;
    size_t sepPos = str.find_first_of(separator);
    size_t prevSepPos = 0;
    while(sepPos != std::string::npos)
    {
      result.push_back(str.substr(prevSepPos, sepPos - prevSepPos));
      prevSepPos = sepPos + 1;
      sepPos = str.find_first_of(separator, prevSepPos);
    }
    result.push_back(str.substr(prevSepPos));
    return result;
  };

  auto validateAndAssignAddrDigit = [](const std::string & digit, uint8_t & addr)
  {
    try
    {
      int fieldInt = std::stoi(digit);
      if (fieldInt < 0 || fieldInt > 255)
        return false;
      addr = (uint8_t)fieldInt;
    }
    catch (...)
    {
      return false;
    }
    return true;
  };

  std::vector<std::string> addrDigits = splitStringBySeparator(addr, '.');
  if (addrDigits.size() != 4)
    return false;

  if (validateAndAssignAddrDigit(addrDigits[0], _addr[0]) == false
   || validateAndAssignAddrDigit(addrDigits[1], _addr[1]) == false
   || validateAndAssignAddrDigit(addrDigits[2], _addr[2]) == false
   || validateAndAssignAddrDigit(addrDigits[3], _addr[3]) == false)
    return false;
  return true;
}
//-----------------------------------------------
bool IPv4::operator>(const IPv4 & lhs) const
{
  return std::tie(lhs._addr[0], lhs._addr[1], lhs._addr[2], lhs._addr[3])
       < std::tie(_addr[0], _addr[1], _addr[2], _addr[3]);
}
//-----------------------------------------------
bool IPv4::operator==(const IPv4 & lhs) const
{
  return std::tie(lhs._addr[0], lhs._addr[1], lhs._addr[2], lhs._addr[3])
      == std::tie(_addr[0], _addr[1], _addr[2], _addr[3]);
}
//-----------------------------------------------
std::ostream & operator<<(std::ostream & os, const IPv4 & ip)
{
  return os << (int)ip._addr[0] << "."
            << (int)ip._addr[1] << "."
            << (int)ip._addr[2] << "."
            << (int)ip._addr[3];
}
//-----------------------------------------------
void sortDescending(VecIPv4 & ips)
{
  auto comp = [&](const IPv4 & lhs, const IPv4 & rhs)
  {
    return lhs > rhs;
  };
  std::sort(ips.begin(), ips.end(), comp);
}
//-----------------------------------------------
void print(const VecIPv4 & ips)
{
  for (auto ip : ips)
  {
    std::cout << ip << '\n';
  }
}
//-----------------------------------------------
VecIPv4 getFilteredStrict(const VecIPv4 & ips, const std::array<int, 4> & filterMask)
{
  VecIPv4 result;
  std::copy_if(ips.begin(), ips.end(), std::back_inserter(result), [&] (const IPv4 & ip)
  {
    if (filterMask[0] >= 0 && filterMask[0] != ip._addr[0])
      return false;
    if (filterMask[1] >= 0 && filterMask[1] != ip._addr[1])
      return false;
    if (filterMask[2] >= 0 && filterMask[2] != ip._addr[2])
      return false;
    if (filterMask[3] >= 0 && filterMask[3] != ip._addr[3])
      return false;
    return true;
  });
  return result;
}
//-----------------------------------------------
VecIPv4 getFilteredAny(const VecIPv4 & ips, const std::array<int, 4> & filterMask)
{
  VecIPv4 result;
  std::copy_if(ips.begin(), ips.end(), std::back_inserter(result), [&] (const IPv4 & ip)
  {
    if (filterMask[0] >= 0 && filterMask[0] == ip._addr[0])
      return true;
    if (filterMask[1] >= 0 && filterMask[1] == ip._addr[1])
      return true;
    if (filterMask[2] >= 0 && filterMask[2] == ip._addr[2])
      return true;
    if (filterMask[3] >= 0 && filterMask[3] == ip._addr[3])
      return true;
    return false;
  });
  return result;
}
//-----------------------------------------------
