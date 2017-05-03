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
#include "../Utils/EventManager.h"
#include "../Events/Event.h"
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

  std::map<std::type_index, System*> systems
  {
    {std::type_index(typeid(InputSystem)), new InputSystem()}
  };
  std::vector<GameObject*> entities;
  std::vector<GameObject*> sprites;

  sprites.push_back(new GameObject(std::vector<Component*> {
	new PositionComponent(19,12),
	  new DirectionComponent(-1,0),
	  new TextureComponent("Media/georg.png",1,2)}));

  curLevel = new Level(sprites, worldMap);

  player = new GameObject();

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
  entities.push_back(player);

  int interval = parser.getInt("cpuwait");

  systems[std::type_index(typeid(InputSystem))]->setRequired(std::vector<std::type_index>
							     {
							       std::type_index(typeid(PositionComponent)),
							       std::type_index(typeid(DirectionComponent)),
							       std::type_index(typeid(SpeedComponent)),
							       std::type_index(typeid(KeyBoardInputComponent))
							     });
  // TODO: Make this return the correct values
  std::cout << systems[std::type_index(typeid(InputSystem))]->isCompatibleWith(sprites[0]) << std::endl;
  std::cout << systems[std::type_index(typeid(InputSystem))]->isCompatibleWith(player) << std::endl;


  player->setOnReceive([](GameObject* obj,Event& e) { std::cout << obj->id << std::endl; });
  EventManager::getInstance()->subscribe(player, Event("event"));

  while(!QuickCG::done()){
    SDL_Delay(interval); //so it consumes less processing power
    player->get<Camera>()->update();
    for(auto it = systems.begin(); it != systems.end(); it++){
      (*it).second->update(entities);
    }
  }
}

