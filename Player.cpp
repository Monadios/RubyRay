#include "/home/gustav/raycastercpp/Player.h"

Player::Player(double px, double py, double dx, double dy, double planX, double planY)
{
  posX = px;
  posY = py;
  dirX = dx;
  dirY = dy;
  planeX = planX;
  planeY = planY;
  rotSpeed = 0;
  moveSpeed = 0.1;
  _input = new KeyBoardInputComponent();
}

void Player::update(std::vector<std::vector<int>> map)
{
  _input->update(this, map);
}
