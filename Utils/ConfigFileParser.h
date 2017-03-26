#ifndef CONFIG_FILE_PARSER_H
#define CONFIG_FILE_PARSER_H

#include <map>
#include <string>
#include <typeindex>

#include "../Utils/json/json.h"
#include "../Classes/Enemy.h"

class ConfigFileParser
{
public:
  ConfigFileParser();
  Json::Value loadFile(std::string filename);
  static const Json::Value VALUE_NOT_FOUND;
  static const std::string DATA_FOLDER;
  Json::Value get(std::string key);
  Json::Value get(std::string key, Json::Value notfound);
  void reloadFile();
  /*
    TODO: Should probably add a get<Type>(variable) function so clients don't
    have to convert it manually every time. At least for simple types i.e built
    in and ubiquitous game classes (Worldmap, GameObject, etc.)
   */

  Json::Value root;

private:
  std::string pathName;
};
#endif
