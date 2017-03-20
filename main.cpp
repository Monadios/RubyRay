#include <chrono>
#include <thread>
#include <cmath>
#include <string>
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
#include "Utils/Camera.h"
using namespace QuickCG;

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

std::vector<GameObject*> sprite;

//function used to sort the sprites
void combSort(int* order, double* dist, int amount);

int main(int /*argc*/, char */*argv*/[])
{
  Player* p = new Player(22,11,-1,0,0,0.66,worldMap);
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  Camera* cam = new Camera(p);
  sprite.push_back(new Enemy(18.5,11.5));
  sprite.push_back(new Barrel(19.5,11.5));


  //start the main loop
  while(!done())
    {
      //timing for input and FPS counter
      oldTime = time;
      time = getTicks();
      double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
      //speed modifiers
      p->moveSpeed = frameTime * 3.0; //the constant value is in squares/second
      p->rotSpeed = frameTime * 2.0; //the constant value is in radians/second
      p->update();
      cam->render(worldMap);
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
