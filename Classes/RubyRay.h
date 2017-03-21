#ifndef RUBY_RAY_H
#define RUBY_RAY_H

#include "Player.h"
#include "../Utils/Level.h"

class Game
{
public:
  Game();
  Player* player;
  Level* level;
  void MainLoop();
private:
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame
};

#endif
