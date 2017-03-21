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
#include "Utils/Level.h"
#include "Classes/RubyRay.h"
using namespace QuickCG;


std::vector<GameObject*> sprites;

int main(int /*argc*/, char */*argv*/[])
{
  Game* game = new Game();
  std::vector<GameObject*> temp = game->level->sprites;

  game->MainLoop();
}

