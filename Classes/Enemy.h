#include "./GameObject.h"

#ifndef ENEMY_H
#define ENEMY_H

struct Enemy : public GameObject
{
  Enemy(double x, double y);
  void update();
};

#endif
