#include <fstream>
#include<iostream>
#include<string>
#include <limits.h>
#include <stdlib.h>

#include "../Utils/ConfigFileParser.h"

ConfigFileParser::ConfigFileParser()
{
  /*
    Maybe this should load lua files instead
   */
}

Json::Value ConfigFileParser::loadFile(std::string path)
{
  char full[PATH_MAX];
  realpath(path.c_str(), full);
  std::cout << full << std::endl;
  std::ifstream config_file(full, std::ios::binary);
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
