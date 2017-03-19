#include "./GameObject.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public GameObject
{
public:
  Enemy(double x, double y);
  void update();
};

#endif
