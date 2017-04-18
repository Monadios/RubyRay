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
  GameObject* player;
  void MainLoop();
private:
  Level* curLevel; // This should be a list of levels
  ConfigFileParser parser;
};

#endif
