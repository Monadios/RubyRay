#include "GameObject.h"

GameObject::GameObject()
{
  id=idCounter++;
}

int GameObject::idCounter = 0;
