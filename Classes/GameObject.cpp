#include "../Classes/GameObject.h"

GameObject::GameObject()
{
  id=idCounter++;
}

GameObject::GameObject(std::vector<Component*> cs)
{
  for(Component* c : cs){
    addComponent(c);
  }

  id=idCounter++;
}

void GameObject::addComponent(Component* c)
{
  std::type_index type = std::type_index(typeid(*c));
  components[type] = c;
}

int GameObject::idCounter = 0;
