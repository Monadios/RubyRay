#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
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

/*
  TODO: Check if map is valid i.e wall along every edge to avoid infinite rays
  and crashing
 */

std::vector<std::vector<int>> worldMap {};

std::vector<GameObject*> sprites;

int main(int /*argc*/, char */*argv*/[])
{
  Json::Value root;

  std::ifstream json_doc("Data/map.json", std::ifstream::binary);
  json_doc >> root;
  for(auto val : root["map"]){
    std::vector<int> temp;
    for(auto square : val){
      temp.push_back(square.asInt());
    }
    worldMap.push_back(temp);
    temp.clear();
  }

  Player* p = new Player(22,11,-1,0,0,0.66,worldMap);
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  sprites.push_back(new Enemy(18.5,11.5));
  sprites.push_back(new Barrel(19.5,11.5));

  std::cout << worldMap[22][11] << std::endl;

  //start the main loop
  while(!done())
    {
      //timing for input and FPS counter
      oldTime = time;
      time = getTicks();
      double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds

      std::for_each(std::begin(sprites), std::end(sprites), [=](GameObject* e)
		    {
		      e->update();
		    });

      p->moveSpeed = frameTime * 3.0; //the constant value is in squares/second
      p->rotSpeed = frameTime * 2.0; //the constant value is in radians/second
      p->update();
      p->camera->render(worldMap, sprites);
    }
}

