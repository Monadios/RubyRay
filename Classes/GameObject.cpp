#include "../Classes/GameObject.h"

void GameObject::addComponent(std::type_index type, Component* c)
{
  components[type] = c;
}

GameObject::GameObject()
{
  id=idCounter++;
}

int GameObject::idCounter = 0;
