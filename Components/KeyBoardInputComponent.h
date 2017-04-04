#ifndef KEYBOARDINPUTCOMPONENT_H
#define KEYBOARDINPUTCOMPONENT_H

class Player;

#include <SDL/SDL.h>
#include <iostream>
#include <memory>

#include "../Classes/Player.h"
#include "../Components/Component.h"
#include "../Utils/quickcg.h"

class KeyBoardInputComponent : public Component
{
public:
  KeyBoardInputComponent( const std::shared_ptr<Player>& _p, std::vector<std::vector<int>> map ) : p(_p), worldMap(map)
  {
    keyboard = {};
  }

  ~KeyBoardInputComponent() = default;

  void update();
  Uint8* keyboard;
private:
  std::vector<std::vector<int>> worldMap;
  const std::shared_ptr<Player>& p;
};

#endif
