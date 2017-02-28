#ifndef ENEMY_H
#define ENEMY_H
#include "./GameObject.h"

struct Enemy : GameObject
{
  Enemy(double x, double y);
  void update(Player* p);
};

#endif
