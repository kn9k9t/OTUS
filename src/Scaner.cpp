#include "Scaner.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
//-----------------------------------------------
void Scaner::printDuplicates() const
{
  std::cout << "Duplicates:" << std::endl;
  for (const auto & pair : _duplicates)
  {
    for (const auto & path : pair.second)
    {
      std::cout << path << "\n";
    }
    std::cout << "\r\n";
  }
}
//-----------------------------------------------
void Scaner::scan()
{
  try
  {
    for(const std::string & dir : _settings._includedDirs)
    {
      if (boost::filesystem::is_directory(dir))
      {
        auto dirIt = boost::filesystem::directory_iterator(dir);
        for (auto & subDir : dirIt)
        {
          scan(subDir);
        }
      }
      else
      {
        scanFile(dir);
      }
    }
  }
  catch (const boost::filesystem::filesystem_error& ex)
  {
    std::cout << "Error while scanning: " << ex.what() << '\n';
  }
}
//-----------------------------------------------
void Scaner::scan(const boost::filesystem::directory_entry & dir)
{
  if (dir.path().string() == "./.qtc_clangd/.cache/clangd/index/overload.hpp.E26650C015D3D476.idx")
    std::cout << "biba";
  if (boost::filesystem::is_directory(dir))
  {
    if (_exclDirs.isExcluded(dir.path().string()))
    {
      std::cout << "Directory: " << dir << " was excluded from scaning" << std::endl;
      return;
    }

    if (_settings._scanLevel == ScanLevel::CurrentDirectory)
      return;

    auto dirIt = boost::filesystem::directory_iterator(dir);
    for (auto & subDir :dirIt)
    {
      scan(subDir);
    }
  }
  else
  {
    scanFile(dir.path().string());
  }
}
//-----------------------------------------------
void Scaner::scanFile(const std::string & path)
{
  if (isPathMatchToMask(path) == false)
    return;

  std::cout << "File: " << path << std::endl;
  if (_files.empty())
  {
    _files.push_back(File(path, _settings._blockSize, &_hasher));
    return;
  }

  if (_files.size() == 1)
    _files[0].readBlock();

  auto newFileIt = _files.emplace(_files.end(), File(path, _settings._blockSize, &_hasher));

  newFileIt->readBlock();

  auto exFileIt = getSimilarFile(*newFileIt);
  if (exFileIt == _files.end())
    return;

  if (recursiveSearchDuplicate(exFileIt, newFileIt) == false)
    return;

  if (_duplicates.count(exFileIt->_blocks) == 0)
    _duplicates[exFileIt->_blocks].push_back(exFileIt->_path);
  _duplicates[newFileIt->_blocks].push_back(newFileIt->_path);
}
//-----------------------------------------------
bool Scaner::isPathMatchToMask(const std::string & path) const
{
  if (_settings._fileMasks.empty())
    return true;

  for (const auto & mask : _settings._fileMasks)
  {
    boost::regex expr(mask);
    boost::smatch what;
    if (boost::regex_match(path, what, expr))
      return true;
  }
  return false;
}
//-----------------------------------------------
bool Scaner::recursiveSearchDuplicate(VecFile::iterator exFileIt, VecFile::iterator newFileIt)
{
  if (exFileIt->_isFullRead && newFileIt->_isFullRead
   && exFileIt->_blocks == newFileIt->_blocks)
    return true;

  if (exFileIt->_blocks.size() <= newFileIt->_blocks.size())
    exFileIt->readBlock();
  newFileIt->readBlock();

  exFileIt = getSimilarFile(*newFileIt);
  if (exFileIt == _files.end())
    return false;

  return recursiveSearchDuplicate(exFileIt, newFileIt);
}
//-----------------------------------------------
VecFile::iterator Scaner::getSimilarFile(const File & file)
{
  auto it = std::find_if(_files.begin(), _files.end(), [&](const File & existingFile)
  {
    if (existingFile._path == file._path)
      return false;
    return existingFile.startsWith(file);
  });
  return it;
}
//-----------------------------------------------
