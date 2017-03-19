#include "./GameObject.h"

#ifndef BARREL_H
#define BARREL_H

struct Barrel : public GameObject
{
  Barrel(double x, double y);
  void update();
};

#endif
