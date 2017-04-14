#ifndef RUBY_RAY_H
#define RUBY_RAY_H

#include <memory>

#include "../Classes/GameObject.h"
#include "../Utils/Level.h"
#include "../Utils/ConfigFileParser.h"

class Game
{
public:
  Game();
  std::shared_ptr<GameObject> player;
  Level* curLevel; // This should be a list of levels
  void MainLoop();
private:
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame
  ConfigFileParser parser;
};

#endif
