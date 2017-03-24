#ifndef KeyBoardInputComponent_H
#define KeyBoardInputComponent_H

class Player;

#include <SDL/SDL.h>

#include "../Classes/Player.h"
#include "../Utils/quickcg.h"

class KeyBoardInputComponent
{
public:
  KeyBoardInputComponent( );
  void update(Player* p, const std::vector<std::vector<int>>& map);
  Uint8* keyboard;
};

#endif
