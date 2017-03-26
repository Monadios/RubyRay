#include "../Classes/Player.h"
#include "../Classes/Component.h"

Player::Player(double px, double py, double dx, double dy,
	       double planX, double planY)
{
  posX = px;
  posY = py;
  dirX = dx;
  dirY = dy;
  rotSpeed = 0;
  moveSpeed = 0.1;
  // TODO: Make this a component as well
  camera = new Camera(px,py,dx,dy);
}

void Player::update()
{
  /*
    Should iterate through components instead
   */
  get<KeyBoardInputComponent>()->update();
  camera->pX = posX;
  camera->pY = posY;
  camera->dX = dirX;
  camera->dY = dirY;
}
