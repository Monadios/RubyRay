#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include "../Utils/quickcg.h"

class Texture
{
public:
  Texture(std::string path);
  Uint32 operator [](int i) const
  {
    return texture[i];
  }
  std::vector<Uint32> texture;
private:
  int texWidth, texHeight;
};
#endif
