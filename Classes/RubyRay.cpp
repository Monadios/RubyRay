#include "./RubyRay.h"
#include <vector>
#include <iostream>
#include "../Classes/GameObject.h"
#include "../Classes/Enemy.h"
#include "../Classes/Barrel.h"
#include "../Utils/json/json.h"
#include "../Utils/ConfigFileParser.h"
#include "Utils/quickcg.h"
#include <fstream>
#include <streambuf>
#include <string>

Game::Game()
{
  std::vector<GameObject*> sprites;
  sprites.push_back(new Enemy(18.5,11.5));
  sprites.push_back(new Barrel(19.5,11.5));

  /*
    TODO:
    Add a LoadLevel(Filename) function
    Check if map is valid i.e wall along every edge to avoid infinite rays
    and crashing
  */

  std::vector<std::vector<int>> worldMap {};
  ConfigFileParser parser = ConfigFileParser();
  parser.loadFile("map.json");
  Json::Value map = parser.get("map");
  // TODO FIgure out what to do with failure
  if(map == ConfigFileParser::VALUE_NOT_FOUND){
    std::cout << "hello\n";
  }
  for(auto val : map){
    std::vector<int> temp;
    for(auto square : val){
      temp.push_back(square.asInt());
    }
    worldMap.push_back(temp);
    temp.clear();
  }

  std::vector<int> coords;
  
  Json::Value playerPos = parser.get("player");
  for(auto coord : playerPos){
    coords.push_back(coord.asInt());
  }
  player = new Player(coords[0],coords[1],-1,0,0,0.66);
  curLevel = new Level(sprites, worldMap);
}

void Game::MainLoop()
{
  while(!QuickCG::done()){
    SDL_Delay(5); //so it consumes less processing power
    oldTime = time;
    time = QuickCG::getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds

    player->moveSpeed = frameTime * 3.0; //the constant value is in squares/second
    player->rotSpeed = frameTime * 2.0; //the constant value is in radians/second
    player->update(curLevel->worldMap);

    std::for_each(std::begin(curLevel->sprites), std::end(curLevel->sprites), [=](GameObject* e)
		  {
		    e->update();
		  });

    player->camera->render(curLevel->worldMap, curLevel->sprites);
    player->camera->drawMiniMap(curLevel->worldMap);
    player->camera->clearScreen();
    player->camera->updateScreen();
    if(player->shoot){
      curLevel->worldMap[int(player->posX)+1][int(player->posY)] = 0;
      player->shoot = false;
    }
  }
}
