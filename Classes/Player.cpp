#include "../Classes/Player.h"

Player::Player(double px, double py, double dx, double dy,
	       double planX, double planY) : GameObject(px,py)
{
  posX = px;
  posY = py;
  dirX = dx;
  dirY = dy;
  rotSpeed = 0;
  moveSpeed = 0.1;
  // TODO: Make this a component as well
}

void Player::update()
{
  /*
    Should iterate through components instead
   */
  get<KeyBoardInputComponent>()->update();
  Camera* camera = get<Camera>();
  camera->pX = posX;
  camera->pY = posY;
  camera->dX = dirX;
  camera->dY = dirY;
  camera->update();
}
