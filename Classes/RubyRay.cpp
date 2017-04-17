#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include "../Classes/RubyRay.h"
#include "../Classes/GameObject.h"
#include "../Utils/json/json.h"
#include "../Utils/quickcg.h"
#include "../Utils/Texture.h"
#include "../Utils/Camera.h"
#include "../Systems/InputSystem.h"
#include "../Systems/System.h"
#include "../Components/TextureComponent.h"
#include "../Components/KeyBoardInputComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/DirectionComponent.h"
#include "../Components/SpeedComponent.h"

Game::Game()
{
  /*
    TODO:
    Add a LoadLevel(Filename) function
    Check if map is valid i.e wall along every edge to avoid infinite rays
    and crashing
  */

}

void Game::MainLoop()
{
  std::vector<std::vector<int>> worldMap {};
  parser = ConfigFileParser();
  parser.loadFile("./Data/map.json");
  Json::Value map = parser.get("map");
  // TODO FIgure out what to do with failure

  for(auto val : map){
    std::vector<int> temp;
    for(auto square : val) {
      temp.push_back(square.asInt());
    };
    worldMap.push_back(temp);
    temp.clear();
  }

  std::vector<System*> systems
  {
    new InputSystem()
  };
  std::vector<GameObject*> entities;
  std::vector<GameObject*> sprites;

  sprites.push_back(new GameObject(std::vector<Component*> {
	new PositionComponent(19,12),
	  new DirectionComponent(-1,0),
	  new TextureComponent("Media/guard.png",1,2)}));

  curLevel = new Level(sprites, worldMap);

  player = std::shared_ptr<GameObject> (new GameObject());

  player->addComponent(new PositionComponent(parser.getDouble("posX"),
					     parser.getDouble("posY")));

  player->addComponent(new DirectionComponent(parser.getDouble("dirX"),
					      parser.getDouble("dirY")));

  double rotFac = parser.getDouble("rotFactor");
  double movFac = parser.getDouble("moveFactor");
  player->addComponent(new SpeedComponent(0,0,rotFac,movFac));
  // player->addComponent(new TextureComponent("Media/guard.png",
  // 					    player->get<PositionComponent>()->x-4,
  // 					    player->get<PositionComponent>()->y));
  player->addComponent(new KeyBoardInputComponent(curLevel->worldMap));
  player->addComponent(new Camera(player,-1,0,curLevel->worldMap, curLevel->sprites));
  entities.push_back(player.get());

  int interval = parser.getInt("cpuwait");
  // systems[0]->setRequired(PositionComponent, DirectionComponent,
  // 			  SpeedComponent, KeyBoardInputComponent);
  std::cout << systems[0]->isCompatibleWith(sprites[0]) << std::endl;

  while(!QuickCG::done()){
    SDL_Delay(interval); //so it consumes less processing power
    player->get<Camera>()->update();
    for(auto it = systems.begin(); it != systems.end(); it++){
      (*it)->update(entities);
    }
  }
}

