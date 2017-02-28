#ifndef KeyBoardInputComponent_H
#define KeyBoardInputComponent_H
struct Player;
#include "/home/gustav/raycastercpp/Classes/Player.h"
#include <SDL/SDL.h>
#include "../Utils/quickcg.h"
struct KeyBoardInputComponent
{
  std::vector<std::vector<int>> worldMap;
  KeyBoardInputComponent();
  void update(Player* p,std::vector<std::vector<int>> map);
  Uint8* keyboard;
};

#endif
