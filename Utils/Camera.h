#ifndef CAMERA_H
#define CAMERA_H

#include "../Classes/Player.h"
#include "../Classes/GameObject.h"
#include "../Utils/quickcg.h"
#include <cmath>
#define numObstacles 2
#define screenWidth 640
#define screenHeight 480

class Camera
{
public:
  Camera(double _x,double _y, double _dx, double _dy);
  void render(const std::vector<std::vector<int>>& worldMap,
	      std::vector<GameObject*> sprites);

  double pX,pY;
  double dX,dY;
  double plX, plY;

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
  //function used to sort the sprites
  void combSort(int* order, double* dist, int amount);
};

#endif
