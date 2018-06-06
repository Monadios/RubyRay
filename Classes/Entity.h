#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <typeindex>
#include <vector>
#include "../Components/Component.h"

class Entity
{
 public:
 Entity(int _id) : id(_id) {}

  int id;

  void addComponent(Component* c);

  template <typename T>
    T* get() {
    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()){
      return dynamic_cast<T*>(it->second);
    }
    return nullptr;
  }

 private:
  std::map<std::type_index, Component*> components;
};

#endif
