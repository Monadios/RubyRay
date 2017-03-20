#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
struct KeyBoardInputComponent;
#include "../Components/KeyBoardInputComponent.h"

class Player
{
public:
  double posX,posY;
  double dirX, dirY; //initial direction vector
  double planeX, planeY = 0.66; //the 2d raycaster version of camera plane
  double rotSpeed;
  double moveSpeed;
  Player(double px, double py, double dx, double dy, double planX, double planY,const std::vector<std::vector<int>>& map);
  void update();
  KeyBoardInputComponent* _input;
};
#endif
