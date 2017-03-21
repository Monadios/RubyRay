#include "./RubyRay.h"
#include <vector>
#include "../Classes/GameObject.h"
#include "../Classes/Enemy.h"
#include "../Classes/Barrel.h"
#include "../Utils/json/json.h"
#include "Utils/quickcg.h"
#include <fstream>

Game::Game()
{
  std::vector<GameObject*> sprites;
  sprites.push_back(new Enemy(18.5,11.5));
  sprites.push_back(new Barrel(19.5,11.5));

  /*
    TODO: Add a LoadLevel(Filename) function
   */

  Json::Value root;
  std::vector<std::vector<int>> worldMap {};
  std::ifstream json_doc("../Data/map.json", std::ifstream::binary);
  json_doc >> root;
  for(auto val : root["map"]){
    std::vector<int> temp;
    for(auto square : val){
      temp.push_back(square.asInt());
    }
    worldMap.push_back(temp);
    temp.clear();
  }


  player = new Player(22,11,-1,0,0,0.66,worldMap);
  level = new Level(sprites, worldMap);
}

void Game::MainLoop()
{
  oldTime = time;
  time = QuickCG::getTicks();
  double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds

  player->moveSpeed = frameTime * 3.0; //the constant value is in squares/second
  player->rotSpeed = frameTime * 2.0; //the constant value is in radians/second
  player->update();

  std::for_each(std::begin(level->sprites), std::end(level->sprites), [=](GameObject* e)
		{
		  e->update();
		});

  player->camera->render(level->worldMap, level->sprites);
}
