#ifndef SYSTEM_H
#define SYSTEM_H

#include<vector>

#include "../Classes/GameObject.h"

class System
{
public:
  virtual void update(std::vector<GameObject*>& entities)=0;
};

#endif
