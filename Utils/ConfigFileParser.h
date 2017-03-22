#ifndef CONFIG_FILE_PARSER_H
#define CONFIG_FILE_PARSER_H

#include "./json/json.h"
#include "./Classes/Enemy.h"
#include <map>
#include <string>
#include <typeindex>

class ConfigFileParser
{
public:
  ConfigFileParser();
  Json::Value loadFile(std::string filename);
  static const int VALUE_NOT_FOUND;
  static const std::string DATA_FOLDER;

  template <typename T>
  T* get() {
    auto it = converters.find(std::type_index(typeid(T)));
    if (it != converters.end()){
      return dynamic_cast<T*>(it->second);
    }
    return nullptr;
  }
  /*
    TODO: Should probably add a get<Type>(variable) function so clients don't
    have to convert it manually every time. At least for simple types i.e built
    in and ubiquitous game classes (Worldmap, GameObject, etc.)
   */
private:
  Json::Value root;
  //Should probably map to Component
  std::map<std::type_index, int> converters {};
};
#endif
