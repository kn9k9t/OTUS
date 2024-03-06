#pragma once
//-----------------------------------------------
#include "Settings.h"
#include <cstdint>
#include <vector>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
//-----------------------------------------------
typedef std::vector<uint8_t> VecChar;
//-----------------------------------------------
class Hash
{
public:
  virtual VecChar hash(const VecChar & block) = 0;
};
//-----------------------------------------------
class BoostHash : public Hash
{
public:
  BoostHash(HashAlgorithm algorithm): _algorithm(algorithm) {}

  virtual VecChar hash(const VecChar & block) override
  {
    switch(_algorithm)
    {
    case HashAlgorithm::CRC32:
      return hashCrc32(block);
    case HashAlgorithm::MD5:
      return hashMd5(block);
    default:
      return VecChar();
    }
  }

private:
  HashAlgorithm _algorithm;

  VecChar hashCrc32(const VecChar & block)
  {
    boost::crc_32_type crc32;
    crc32.process_bytes(block.data(), block.size());
    uint checkSum = crc32.checksum();
    char * hash = reinterpret_cast<char *>(&checkSum);
    return VecChar(hash, hash + sizeof(hash));
  }

  VecChar hashMd5(const VecChar & block)
  {
    boost::uuids::detail::md5 md5;
    boost::uuids::detail::md5::digest_type digest;
    md5.process_bytes(block.data(), block.size());
    md5.get_digest(digest);
    char * hash = reinterpret_cast<char *>(&digest);
    return VecChar(hash, hash + sizeof(hash));
  }
};
//-----------------------------------------------
