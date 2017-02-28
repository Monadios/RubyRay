#include "./Player.h"

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
struct GameObject
{
  double x;
  double y;
  int texture;

  virtual void update(Player* p)=0;
};

#endif
