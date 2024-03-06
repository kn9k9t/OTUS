#include "Settings.h"
#include <iostream>
#include <boost/program_options.hpp>
//-----------------------------------------------
namespace CmdOpt = boost::program_options;
//-----------------------------------------------
bool Settings::fillFromArgs(int argc, char ** argv)
{
  auto checkDepthValue = [](const int & value)
  {
    if (value != 0 && value != 1) throw CmdOpt::validation_error(CmdOpt::validation_error::invalid_option_value, "depth");
   };

  auto checkSizeValue = [](const int & value)
  {
    if (value < 1) throw CmdOpt::validation_error(CmdOpt::validation_error::invalid_option_value, "block-size");
  };

  auto checkAlgorithmValue = [](const std::string & value)
  {
    if (value == "CRC32"
     || value == "MD5")
      return;
    throw CmdOpt::validation_error(CmdOpt::validation_error::invalid_option_value, "algorithm");
  };

  try
  {
    CmdOpt::options_description desc("Allowed options: ");
    desc.add_options()
      ("help,h", "help message")
      ("include-dirs,i", CmdOpt::value<VecString>()->default_value(VecString{"."}, ".")->multitoken()->composing(), "Including to search directories, can be multiple. Default is current folder")
      ("exclude-dirs,e", CmdOpt::value<VecString>()->multitoken()->composing(), "Excluded to search directories, can be multiple")
      ("depth,d", CmdOpt::value<int>()->default_value(0)->notifier(checkDepthValue), "Scan depth, 1 - all directories, 0 - current folder only. Default value is 0")
      ("min-size,m", CmdOpt::value<int>()->default_value(1)->notifier(checkSizeValue), "Minimum size of the processed file in bytes. Default value is 1")
      ("file-masks,f", CmdOpt::value<VecString>()->multitoken()->composing(), "Masks for the files participating in comparison")
      ("block-size,b", CmdOpt::value<int>()->default_value(256)->notifier(checkSizeValue), "The size in bytes of the block to read the files with. Default value is 256")
      ("algorithm,a", CmdOpt::value<std::string>()->default_value("CRC32")->notifier(checkAlgorithmValue), "Hashing algorithm to hash file blocks. Default value is CRC32");

    CmdOpt::variables_map vm;
    CmdOpt::store(CmdOpt::parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return false;
    }

    _includedDirs = vm["include-dirs"].as<VecString>();
    if (vm.count("exclude-dirs"))
      _excludedDirs = vm["exclude-dirs"].as<VecString>();
    if (vm.count("file-masks"))
      _fileMasks = vm["file-masks"].as<VecString>();

    _scanLevel = ScanLevel(vm["depth"].as<int>());
    _minFileSize = (uint)vm["min-size"].as<int>();
    _blockSize = (uint)vm["block-size"].as<int>();
    if (vm["algorithm"].as<std::string>() == "CRC32")
      _hashAlgorithm = HashAlgorithm::CRC32;
    if (vm["algorithm"].as<std::string>() == "MD5")
      _hashAlgorithm = HashAlgorithm::MD5;
  }
  catch(const boost::program_options::error & ex)
  {
    std::cout << "Error while setuping: " << ex.what() << '\n';
  }
  return true;
}
//-----------------------------------------------
std::ostream & operator<<(std::ostream & os, const Settings & obj)
{
  os << "include-dirs: " << PrintVector(obj._includedDirs) << "\n"
     << "exclude-dirs: " << PrintVector(obj._excludedDirs) << "\n"
     << "depth: "        << (int)obj._scanLevel            << "\n"
     << "min-size: "     << obj._minFileSize               << "\n"
     << "file-masks: "   << PrintVector(obj._fileMasks)    << "\n"
     << "block-size: "   << obj._blockSize                 << "\n"
     << "algorithm: "    << (int)obj._hashAlgorithm        << std::endl;
  return os;
}
//-----------------------------------------------
