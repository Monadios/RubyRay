#include <fstream>

#include "../Utils/ConfigFileParser.h"

ConfigFileParser::ConfigFileParser()
{
}

Json::Value ConfigFileParser::loadFile(std::string path)
{
  std::ifstream config_file(path, std::ios::binary);
  pathName = path;
  config_file >> root;
  return root;
}

Json::Value ConfigFileParser::get(std::string key)
{
  return root.get(key, VALUE_NOT_FOUND);
}

void ConfigFileParser::reloadFile()
{
  std::ifstream config_file(DATA_FOLDER + pathName, std::ios::binary);
  config_file >> root;
}

const std::string ConfigFileParser::DATA_FOLDER = "./Data/";
const Json::Value ConfigFileParser::VALUE_NOT_FOUND = Json::Value::null;
