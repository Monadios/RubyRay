#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../Classes/Entity.h"

class EntityFactory
{
 public:
  EntityFactory();
  Entity generateEntity();
  
 private:
  static int idCounter;
};

#endif
