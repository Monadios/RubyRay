#include "../Classes/EntityFactory.h"
#include "../Classes/Entity.h"
EntityFactory::EntityFactory()
{
}

int EntityFactory::idCounter = 0;


Entity EntityFactory::generateEntity()
{
  return Entity(idCounter++);
}
