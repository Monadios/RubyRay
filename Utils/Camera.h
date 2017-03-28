#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

class Player;

#include "../Classes/GameObject.h"
#include "../Utils/quickcg.h"
#include "../Classes/Player.h"
#include "../Classes/Component.h"


//These should be loaded from file or as an argument
#define screenWidth 640
#define screenHeight 480

class Camera : public Component
{
public:
  Camera(double _x,double _y, double _dx, double _dy,
	 const std::vector<std::vector<int>>& worldMap,
	 std::vector<GameObject*> sprites);

  void render();
  void drawMiniMap(const std::vector<std::vector<int>>& worldMap);

  /*
    Note: these to functions should proably be made private
   */

  void update()
  {
    if(draw){
      render();
    }
  }

  void clearScreen();
  void updateScreen() const;

  double pX,pY;
  double dX,dY;
  double plX, plY;
  bool drawScreen = true;
private:
  Player* player;
  std::vector<Uint32> texture[12];
  Uint32 buffer[screenHeight][screenWidth];
  //1D Zbuffer
  double ZBuffer[screenWidth];
  //arrays used to sort the sprites
  std::vector<int> spriteOrder;
  std::vector<double> spriteDistance;
  double currentDist;
  //function used to sort the sprites
  void combSort(std::vector<int> order, std::vector<double> dist, int amount);
};

#endif
