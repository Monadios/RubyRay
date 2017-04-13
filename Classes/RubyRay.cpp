#include <vector>
#include <iostream>
#include <string>

#include "../Classes/RubyRay.h"
#include "../Classes/GameObject.h"
#include "../Utils/json/json.h"
#include "../Utils/ConfigFileParser.h"
#include "../Utils/quickcg.h"
#include "../Utils/Texture.h"
#include "../Classes/Player.h"
#include "../Components/TextureComponent.h"

Game::Game()
{
  std::vector<GameObject*> sprites;
  sprites.push_back(new GameObject(18.5,12,
			      std::vector<Component*> {
				new TextureComponent("Media/guard.png",1,2)}));
  /*
    TODO:
    Add a LoadLevel(Filename) function
    Check if map is valid i.e wall along every edge to avoid infinite rays
    and crashing
  */

  std::vector<std::vector<int>> worldMap {};
  ConfigFileParser parser = ConfigFileParser();
  parser.loadFile("./Data/map.json");
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

  player = std::shared_ptr<Player> (new Player(parser.getDouble("posX"),
					       parser.getDouble("posY"),
					       parser.getDouble("dirX"),
					       parser.getDouble("dirY"),
					       parser.getDouble("planeX"),
					       parser.getDouble("planeY")));

  curLevel = new Level(sprites, worldMap);
  player->addComponent(new KeyBoardInputComponent(player,curLevel->worldMap));
  player->addComponent(new Camera(player->posX,player->posY,-1,0,
				  curLevel->worldMap, curLevel->sprites));

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
    player->update();

    std::for_each(std::begin(curLevel->sprites), std::end(curLevel->sprites), [=](GameObject* e)
		  {
		    e->update();
		  });
  }
}

