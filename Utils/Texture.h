#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include "../Utils/quickcg.h"

class Texture
{
public:
  Texture(std::string path);
private:
  std::vector<Uint32> texture;
  int texWidth, texHeight;
};
#endif
