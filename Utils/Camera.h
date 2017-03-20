#ifndef CAMERA_H
#define CAMERA_H

#include "../Classes/Player.h"

#define numObstacles 2
#define screenWidth 640
#define screenHeight 480

class Camera
{
public:
  Camera(Player* p);
  int x;
  int y;
  void render(const std::vector<std::vector<int>>& worldMap);

private:
  Player* player;
  std::vector<Uint32> texture[12];
  Uint32 buffer[screenHeight][screenWidth];
  //1D Zbuffer
  double ZBuffer[screenWidth];
  //arrays used to sort the sprites
  int spriteOrder[numObstacles];
  double spriteDistance[numObstacles];
  double currentDist;
};

#endif
