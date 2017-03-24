#include "Classes/RubyRay.h"
using namespace QuickCG;


std::vector<GameObject*> sprites;

int main(int /*argc*/, char */*argv*/[])
{
  Game* game = new Game();
  game->MainLoop();
}

