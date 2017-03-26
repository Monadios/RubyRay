#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Camera;
class KeyBoardInputComponent;

#include "../Classes/GameObject.h"
#include "../Utils/Camera.h"
#include "../Components/KeyBoardInputComponent.h"

class Player : public GameObject
{
public:
  double rotSpeed;
  double moveSpeed;
  Player(double px, double py, double dx, double dy, double planX, double planY);
  void update();
  double posX,posY;
  double dirX, dirY; //initial direction vector
  Camera* camera;
  bool moving = true;
  bool shoot = false;
};
#endif
