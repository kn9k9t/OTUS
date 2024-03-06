#pragma once
//-----------------------------------------------
#include <string>
#include <vector>
//-----------------------------------------------
typedef std::vector<std::string> VecString;
//-----------------------------------------------
enum class ScanLevel
{
  CurrentDirectory  = 0,
  IncludedDirectory = 1
};
//-----------------------------------------------
enum class HashAlgorithm
{
  CRC32,
  MD5
};
//-----------------------------------------------
struct Settings
{
  VecString     _includedDirs;
  VecString     _excludedDirs;
  ScanLevel     _scanLevel;
  uint          _minFileSize;
  VecString     _fileMasks;
  uint          _blockSize;
  HashAlgorithm _hashAlgorithm;

  bool fillFromArgs(int argc, char ** argv);
};
std::ostream & operator<<(std::ostream & os, const Settings & obj);
//-----------------------------------------------
template <typename T>
struct PrintVector
{
  PrintVector(const std::vector<T> & vec): _vec(vec) {}
  std::vector<T> _vec;
};

template <typename T>
std::ostream & operator<<(std::ostream & os, const PrintVector<T> & obj)
{
  if(obj._vec.empty())
  {
    os << std::string("<null>");
    return os;
  }
  auto last = std::prev(obj._vec.end());
  for (auto it = obj._vec.begin(); it != obj._vec.end(); ++it)
  {
    if (it != last)
      os << *it << ", ";
    else
      os << *it;
  }
  return os;
};
//-----------------------------------------------
