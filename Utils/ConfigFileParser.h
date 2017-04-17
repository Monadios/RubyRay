#ifndef CONFIG_FILE_PARSER_H
#define CONFIG_FILE_PARSER_H

#include <map>
#include <string>
#include <typeindex>
#include <libconfig.h++>
#include "../Utils/json/json.h"

class ConfigFileParser
{
public:
  ConfigFileParser();

  /*
    This should have a map<filename, jsonValue> variable that is loaded at
    startup.
    Also this class should probably be a singleton
   */

  Json::Value loadFile(std::string filename);
  static const Json::Value VALUE_NOT_FOUND;
  static const std::string DATA_FOLDER;
  Json::Value get(std::string key, Json::Value def=VALUE_NOT_FOUND);
  std::string getString(std::string key, Json::Value def=VALUE_NOT_FOUND);
  double getDouble(std::string key, Json::Value def=VALUE_NOT_FOUND);
  int getInt(std::string key, Json::Value def=VALUE_NOT_FOUND);

  void reloadFile();

Json::Value root;

private:
  std::string pathName;
  std::map<std::string, Json::Value> files;
};
#endif
