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

Json::Value ConfigFileParser::get(std::string key)
{
  return root.get(key, VALUE_NOT_FOUND);
}

Json::Value ConfigFileParser::get(std::string key, Json::Value notfound)
{
  return root.get(key, notfound);
}

const std::string ConfigFileParser::DATA_FOLDER = "./Data/";
const Json::Value ConfigFileParser::VALUE_NOT_FOUND = Json::Value::null;
