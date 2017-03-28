#include "../Classes/GameObject.h"

GameObject::GameObject(double _x, double _y)
{
  x = _x;
  y = _y;
  id=idCounter++;
}

GameObject::GameObject(double _x, double _y, std::vector<Component*> cs)
{
  for(Component* c : cs){
    addComponent(c);
  }

  x = _x;
  y = _y;
  id=idCounter++;
}

void GameObject::addComponent(Component* c)
{
  std::type_index type = std::type_index(typeid(*c));
  components[type] = c;
}

int GameObject::idCounter = 0;
