#include "ConfigFileParser.h"
#include <string>
#include <fstream>

ConfigFileParser::ConfigFileParser()
{
}

Json::Value ConfigFileParser::loadFile(std::string path)
{
  std::ifstream config_file(path, std::ios::binary);
  config_file >> root;
  return root;
}
