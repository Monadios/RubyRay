#ifndef CONFIG_FILE_PARSER_H
#define CONFIG_FILE_PARSER_H

#include "./json/json.h"

class ConfigFileParser
{
public:
  ConfigFileParser();
  Json::Value loadFile(std::string filename);
  static const int VALUE_NOT_FOUND = -1;
private:
  Json::Value root;
};
#endif
