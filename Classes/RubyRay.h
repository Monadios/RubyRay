#ifndef RUBY_RAY_H
#define RUBY_RAY_H

#include <memory>

#include "../Classes/Player.h"
#include "../Utils/Level.h"

class Game
{
public:
  Game();
  std::shared_ptr<Player> player;
  Level* curLevel; // This should be a list of levels
  void MainLoop();
private:
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame
};

#endif
