#ifndef KeyBoardInputComponent_H
#define KeyBoardInputComponent_H

class Player;

#include <SDL/SDL.h>

#include "../Classes/Player.h"
#include "../Classes/Component.h"
#include "../Utils/quickcg.h"

class KeyBoardInputComponent : public Component
{
public:
  KeyBoardInputComponent( Player* _p, std::vector<std::vector<int>> map ) : p(_p), worldMap(map)
  {
    keyboard = {};
  }

  void update();
  Uint8* keyboard;
private:

  /*
    TODO: Make this a const reference
   */
  std::vector<std::vector<int>> worldMap;
  Player* p;
};

#endif
