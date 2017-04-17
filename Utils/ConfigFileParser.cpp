#include <fstream>

#include "../Utils/ConfigFileParser.h"

ConfigFileParser::ConfigFileParser()
{
  /*
    Maybe this should load lua files instead
   */
}

Json::Value ConfigFileParser::loadFile(std::string path)
{
  std::ifstream config_file(path, std::ios::binary);
  pathName = path;
  config_file >> root;
  return root;
}

Json::Value ConfigFileParser::get(std::string key, Json::Value def)
{
  return root.get(key, def);
}

std::string ConfigFileParser::getString(std::string key, Json::Value def)
{
  return root.get(key, def).asString();
}

double ConfigFileParser::getDouble(std::string key, Json::Value def)
{
  return root.get(key, def).asDouble();
}

int ConfigFileParser::getInt(std::string key, Json::Value def)
{
  return root.get(key, def).asInt();
}

void ConfigFileParser::reloadFile()
{
  std::ifstream config_file(DATA_FOLDER + pathName, std::ios::binary);
  config_file >> root;
}

const std::string ConfigFileParser::DATA_FOLDER = "./Data/";
const Json::Value ConfigFileParser::VALUE_NOT_FOUND = Json::Value::null;
