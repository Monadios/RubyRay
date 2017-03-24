#include "../Classes/GameObject.h"

#ifndef BARREL_H
#define BARREL_H

class Barrel : public GameObject
{
public:
  Barrel(double x, double y);
  void update();
};

#endif
