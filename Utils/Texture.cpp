#include "../Utils/Texture.h"
#include <iostream>

Texture::Texture(std::string path)
{
  texWidth = 64;
  texHeight = 64;
  unsigned long tw, th, error = 0;
  error |= QuickCG::loadImage(texture, tw, th, path);
  //TODO: Add actual error handling (throw exception)
  if(error) { std::cout << "error loading images" << std::endl; }
  texture.resize(texWidth * texHeight);
}
