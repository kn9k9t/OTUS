#pragma once
//-----------------------------------------------
#include "Hash.h"
#include <vector>
#include <string>
#include <list>
#include <fstream>
//-----------------------------------------------
typedef std::vector<uint8_t> VecChar;
//-----------------------------------------------
struct File
{
  std::string        _path;
  std::ifstream      _fileStream;
  std::list<VecChar> _blocks;
  uint               _blockSize;
  Hash *             _hasher;
  bool               _isFullRead;

  File(const std::string & path, uint blockSize, Hash * hasher):
    _path(path),
    _fileStream(_path),
    _blockSize(blockSize),
    _hasher(hasher),
    _isFullRead(false) {}

  bool startsWith(const File & file) const
  {
    if (file._blocks.size() > _blocks.size())
      return false;

    auto lhs = _blocks.begin();
    auto rhs = file._blocks.begin();
    for (; rhs != file._blocks.end(); )
    {
      if (*lhs != *rhs)
        return false;

      ++lhs;
      ++rhs;
    }

    return true;
  }

  void readBlock()
  {
    if (_isFullRead)
      return;

    VecChar buffer(_blockSize, '\0');
    _fileStream.read((char*)buffer.data(), _blockSize);
    if (_fileStream.eof() || std::count(buffer.begin(), buffer.end(), '\0') == _blockSize)
    {
      _isFullRead = true;
      _fileStream.close();
    }
    _blocks.push_back(_hasher->hash(buffer));
  }
};
//-----------------------------------------------
