#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
struct KeyBoardInputComponent;
class Camera;
#include "../Components/KeyBoardInputComponent.h"
#include "../Utils/Camera.h"

class Player
{
public:
  double rotSpeed;
  double moveSpeed;
  Player(double px, double py, double dx, double dy, double planX,
	 double planY);
  void update(const std::vector<std::vector<int>>& map);
  double posX,posY;
  double dirX, dirY; //initial direction vector
  Camera* camera;
  bool moving = true;
  bool shoot = false;
private:
  KeyBoardInputComponent* _input;
};
#endif
