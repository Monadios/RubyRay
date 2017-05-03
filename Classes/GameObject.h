#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <map>
#include <typeindex>
#include <vector>
#include <functional>
#include "../Components/Component.h"
#include "../Events/Event.h"

class GameObject
{
public:
  GameObject();
  GameObject(std::vector<Component*> cs);

  int id;
  std::map<std::type_index, Component*> components;

  void addComponent(Component* c);
  void update(){
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

  void setOnReceive(std::function<void(GameObject*, Event*)> f) { onReceive = f; }

  void receive(GameObject* obj, Event* e){
    if(onReceive){
      onReceive(obj, e);
    }
  }

private:
  static int idCounter;
  std::function<void(GameObject*, Event*)> onReceive;
};

#endif
