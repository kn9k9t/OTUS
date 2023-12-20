#pragma once
//-----------------------------------------------
#include <string>
//-----------------------------------------------
/*
 * Class to handle files
 *
 * @tparam FileContent the type of data with which handler will working
 * */
template <typename FileContent>
class FileHandler
{
public:
  FileHandler(){}
  /*
   * @param path to the file
   * @return content of the file
   * */
  FileContent readFile(const std::string & path);
  /*
   * @param content to safe
   * */
  void safeFile(const FileContent & content);
  /*
   * @param path to the file
   * */
  void deleteField(const std::string & path);
};
//-----------------------------------------------
