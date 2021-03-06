#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <memory>

class Player;

#include "../Classes/GameObject.h"
#include "../Utils/quickcg.h"
#include "../Components/Component.h"
#include "../Utils/ConfigFileParser.h"


//These should be loaded from file or as an argument
#define screenWidth 480
#define screenHeight 360

class Camera : public Component
{
public:
  Camera(GameObject* _obj, double _dx, double _dy,
	 std::vector<std::vector<int>>& map,
	 std::vector<GameObject*> sprites);

  void render(bool floorceil);
  void drawMiniMap();
  void sendMessage(Msg msg) {}
  /*
    Note: these to functions should proably be made private
   */

  void update();
  void clearScreen();
  void updateScreen() const;

  double pX,pY;
  double dX,dY;
  double plX, plY;
  GameObject* obj;
private:
  ConfigFileParser parser;
  int texHeight;
  int texWidth;
  Uint32 floorColor;
  Uint32 ceilColor;
  std::vector<Uint32> texture[12];
  Uint32 buffer[screenHeight][screenWidth];
  //1D Zbuffer
  double ZBuffer[screenWidth];
  //arrays used to sort the sprites
  std::vector<int> spriteOrder;
  std::vector<GameObject*> sprites;
  std::vector<double> spriteDistance;
  double currentDist;
  std::vector<std::vector<int>>& worldMap;
  //function used to sort the sprites
  void combSort(std::vector<int> order, std::vector<double> dist, int amount);
};

#endif
