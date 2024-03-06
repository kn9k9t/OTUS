#pragma once
//-----------------------------------------------
#include "File.h"
#include "Settings.h"
#include "Hash.h"
#include <algorithm>
#include <boost/filesystem.hpp>
//-----------------------------------------------
class ExcludeDirs
{
public:
  ExcludeDirs(const VecString & dirs): _dirs(dirs)
  {
    for (auto & dir : _dirs)
    {
      if (dir.back() == '/')
        dir.pop_back();
    }
  }

  bool isExcluded(const std::string & dir) { return std::count(_dirs.begin(), _dirs.end(), dir) != 0; }
private:
  VecString _dirs;
};
//-----------------------------------------------
typedef std::vector<File> VecFile;
//-----------------------------------------------
class Scaner
{
public:
  Scaner(const Settings & settings):
    _hasher(settings._hashAlgorithm),
    _settings(settings),
    _exclDirs(settings._excludedDirs) {}

  void printDuplicates() const;
  void scan();

private:
  VecFile _files;
  std::map<std::list<VecChar>, VecString> _duplicates;

  BoostHash         _hasher;
  Settings          _settings;
  ExcludeDirs       _exclDirs;


  void scan(const boost::filesystem::directory_entry & dir);
  void scanFile(const std::string & path);
  bool isPathMatchToMask(const std::string & path) const;

  bool recursiveSearchDuplicate(VecFile::iterator exFileIt, VecFile::iterator newFileIt);
  VecFile::iterator getSimilarFile(const File & file);
};
//-----------------------------------------------
