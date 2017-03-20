#include "./Player.h"
Player::Player(double px, double py, double dx, double dy, double planX, double
planY, const std::vector<std::vector<int>>& map)
{
  posX = px;
  posY = py;
  dirX = dx;
  dirY = dy;
  rotSpeed = 0;
  moveSpeed = 0.1;
  _input = new KeyBoardInputComponent(map);
  camera = new Camera(px,py,dx,dy);
}

void Player::update()
{
  _input->update(this);
  camera->pX = posX;
  camera->pY = posY;
  camera->dX = dirX;
  camera->dY = dirY;
}
