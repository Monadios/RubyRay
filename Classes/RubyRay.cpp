#include <vector>
#include <iostream>
#include <string>

#include "../Classes/RubyRay.h"
#include "../Classes/GameObject.h"
#include "../Utils/json/json.h"
#include "../Utils/quickcg.h"
#include "../Utils/Texture.h"
#include "../Utils/Camera.h"
#include "../Components/TextureComponent.h"
#include "../Components/KeyBoardInputComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/DirectionComponent.h"
#include "../Components/SpeedComponent.h"

Game::Game()
{
  std::vector<GameObject*> sprites;
  sprites.push_back(new GameObject(std::vector<Component*> {
	new PositionComponent(19,12),
	new TextureComponent("Media/guard.png",1,2)}));
  /*
    TODO:
    Add a LoadLevel(Filename) function
    Check if map is valid i.e wall along every edge to avoid infinite rays
    and crashing
  */

  std::vector<std::vector<int>> worldMap {};
  parser = ConfigFileParser();
  parser.loadFile("./Data/map.json");
  Json::Value map = parser.get("map");
  // TODO FIgure out what to do with failure
  if(map == ConfigFileParser::VALUE_NOT_FOUND){
    std::cout << "hello\n";
  }

  for(auto val : map){
    std::vector<int> temp;
    for(auto square : val) {
      temp.push_back(square.asInt());
    };
    worldMap.push_back(temp);
    temp.clear();
  }

  player = std::shared_ptr<GameObject> (new GameObject());
  curLevel = new Level(sprites, worldMap);

  player->addComponent(new PositionComponent(parser.getDouble("posX"),
					     parser.getDouble("posY")));

  player->addComponent(new DirectionComponent(parser.getDouble("dirX"),
					      parser.getDouble("dirY")));

  player->addComponent(new SpeedComponent(0,0));

  player->addComponent(new KeyBoardInputComponent(player,curLevel->worldMap));
  player->addComponent(new Camera(player,-1,0,curLevel->worldMap, curLevel->sprites));
}

void Game::MainLoop()
{
  double rotFac = parser.getDouble("rotFactor");
  double movFac = parser.getDouble("moveFactor");

  /*
    Ideally this function should simply be operating on a list of systems
    i.e for system in systems : system.update(entities w. required components)
   */

  while(!QuickCG::done()){
    SDL_Delay(5); //so it consumes less processing power
    oldTime = time;
    time = QuickCG::getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
    player->get<SpeedComponent>()->moveSpeed = frameTime * movFac; //the constant value is in squares/second
    player->get<SpeedComponent>()->rotSpeed = frameTime * rotFac; //the constant value is in radians/second
    player->update();

    std::for_each(std::begin(curLevel->sprites), std::end(curLevel->sprites), [=](GameObject* e)
		  {
		    e->update();
		  });
  }
}

