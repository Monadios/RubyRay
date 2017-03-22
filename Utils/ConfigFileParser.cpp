#include "ConfigFileParser.h"
#include <fstream>

ConfigFileParser::ConfigFileParser()
{
}

Json::Value ConfigFileParser::loadFile(std::string path)
{
  std::ifstream config_file(DATA_FOLDER + path, std::ios::binary);
  config_file >> root;
  return root;
}

const std::string ConfigFileParser::DATA_FOLDER = "./Data/";
const int ConfigFileParser::VALUE_NOT_FOUND = -1;
