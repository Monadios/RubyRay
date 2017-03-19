#include "./Component.h"
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <map>
#include <string>
#include <typeindex>

class GameObject
{
public:
  double x;
  double y;
  int texture;
  std::map<std::type_index, Component*> components;

  void addComponent(std::type_index, Component* c);
  virtual void update()=0;
  template <typename T>
  T* get() {
    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()){
      return dynamic_cast<T*>(it->second);
    }
    return nullptr;
  }
};

#endif
