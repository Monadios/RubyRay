#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <map>
#include <typeindex>
#include <vector>

#include "../Components/Component.h"

class GameObject
{
public:
  GameObject();
  GameObject(std::vector<Component*> cs);

  int id;
  std::map<std::type_index, Component*> components;

  void addComponent(Component* c);
  virtual void update(){
    for(const auto& pair : components ){
      pair.second->update();
    }
  };
  template <typename T>
  T* get() {
    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()){
      return dynamic_cast<T*>(it->second);
    }
    return nullptr;
  }
private:
  static int idCounter;
};

#endif
