/**
 * \brief This is the base class for any interactable object in the game
 */


#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <map>
#include <typeindex>
#include "../Classes/Component.h"

class GameObject
{
public:
  double x;
  double y;
  GameObject();
  int texY;
  int width;
  int texture;
  int id;
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
private:
  static int idCounter;
};

#endif
