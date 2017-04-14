#ifndef LEVEL_H
#define LEVEL_H

#include<vector>

class Level
{
public:
  Level(std::vector<GameObject*> s, std::vector<std::vector<int>> m) :
  sprites(s), worldMap(m){}
  std::vector<GameObject*> sprites;
  std::vector<std::vector<int>> worldMap {};
};
#endif
