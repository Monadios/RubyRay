#ifndef KeyBoardInputComponent_H
#define KeyBoardInputComponent_H
class Player;
#include "../Classes/Player.h"
#include <SDL/SDL.h>
#include "../Utils/quickcg.h"
class KeyBoardInputComponent
{
public:
  std::vector<std::vector<int>> worldMap;
  KeyBoardInputComponent( );
  void update(Player* p, const std::vector<std::vector<int>>& map);
  Uint8* keyboard;
};

#endif
