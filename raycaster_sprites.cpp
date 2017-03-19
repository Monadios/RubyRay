#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <SDL/SDL.h>
#include "Utils/quickcg.h"
#include "Utils/json/json.h"
#include "Classes/Player.h"
#include "Classes/Enemy.h"
#include "Classes/Barrel.h"
#include "Classes/GameObject.h"
using namespace QuickCG;

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64

double currentDist;

const std::vector<std::vector<int>> worldMap
{
    {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
    {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
    {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
    {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
    {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
    {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
    {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
  };

#define numObstacles 2

std::vector<GameObject*> sprite;

Uint32 buffer[screenHeight][screenWidth];

//1D Zbuffer
double ZBuffer[screenWidth];

//arrays used to sort the sprites
int spriteOrder[numObstacles];
double spriteDistance[numObstacles];

//function used to sort the sprites
void combSort(int* order, double* dist, int amount);

int main(int /*argc*/, char */*argv*/[])
{
  Player* p = new Player(22,11,-1,0,0,0.66);
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  sprite.push_back(new Enemy(18.5,11.5));
  sprite.push_back(new Barrel(19.5,11.5));

  std::vector<Uint32> texture[12];
  for(int i = 0; i < 11; i++) texture[i].resize(texWidth * texHeight);

  Json::Value root;
  std::ifstream config_doc("Data/test.json", std::ifstream::binary);

  screen(screenWidth,screenHeight, 0, "Raycaster");

  //load some textures
  unsigned long tw, th, error = 0;
  error |= loadImage(texture[0], tw, th, "Media/eagle.png");
  error |= loadImage(texture[1], tw, th, "Media/redbrick.png");
  error |= loadImage(texture[2], tw, th, "Media/purplestone.png");
  error |= loadImage(texture[3], tw, th, "Media/greystone.png");
  error |= loadImage(texture[4], tw, th, "Media/bluestone.png");
  error |= loadImage(texture[5], tw, th, "Media/mossy.png");
  error |= loadImage(texture[6], tw, th, "Media/wood.png");
  error |= loadImage(texture[7], tw, th, "Media/colorstone.png");

  //load some sprite textures
  unsigned long gw;
  unsigned long gh;
  error |= loadImage(texture[8], tw, th, "Media/barrel.png");
  error |= loadImage(texture[9], tw, th, "Media/pillar.png");
  error |= loadImage(texture[10], tw, th, "Media/greenlight.png");
  error |= loadImage(texture[11], tw, th, "Media/guard.png");
  if(error) { std::cout << "error loading images" << std::endl; return 1; }

  //start the main loop
  while(!done())
    {
      //timing for input and FPS counter
      oldTime = time;
      time = getTicks();
      double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
      redraw();


      //speed modifiers
      p->moveSpeed = frameTime * 3.0; //the constant value is in squares/second
      p->rotSpeed = frameTime * 2.0; //the constant value is in radians/second
      p->update(worldMap);
    }
}

//sort algorithm
void combSort(int* order, double* dist, int amount)
{
  int gap = amount;
  bool swapped = false;
  while(gap > 1 || swapped)
    {
      //shrink factor 1.3
      gap = (gap * 10) / 13;
      if(gap == 9 || gap == 10) gap = 11;
      if (gap < 1) gap = 1;
      swapped = false;
      for (int i = 0; i < amount - gap; i++)
	{
	  int j = i + gap;
	  if (dist[i] < dist[j])
	    {
	      std::swap(dist[i], dist[j]);
	      std::swap(order[i], order[j]);
	      swapped = true;
	    }
	}
    }
}
