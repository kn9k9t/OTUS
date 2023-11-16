#ifndef IPV4_H
#define IPV4_H
//-----------------------------------------------
#include <array>
#include <string>
#include <vector>
#include <iostream>
//-----------------------------------------------
struct IPv4
{
  std::array<uint8_t, 4> _addr;

  IPv4() : _addr({0, 0, 0, 0}) {};
  bool fill(const std::string & addr);
  bool operator>(const IPv4 & lhs) const;
  bool operator==(const IPv4 & lhs) const;
};
//-----------------------------------------------
std::ostream & operator<<(std::ostream & os, const IPv4 & ip);
//-----------------------------------------------
typedef std::vector<IPv4> VecIPv4;
//-----------------------------------------------
void sort(VecIPv4 & ips);
void print(const VecIPv4 & ips);
VecIPv4 getFilteredStrict(const VecIPv4 & ips, const std::array<int, 4> & filterMask);
VecIPv4 getFilteredAny(const VecIPv4 & ips, const std::array<int, 4> & filterMask);
//-----------------------------------------------
#endif // IPV4_H
