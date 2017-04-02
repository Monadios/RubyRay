#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include <string>

#include "../Utils/Texture.h"
#include "../Components/Component.h"

class TextureComponent : public Component
{
public:
  TextureComponent(std::string path, double h, double w) :
    texture(Texture(path)), heightFactor(h),widthFactor(w) {}

  void setHeightFactor(int fac){
    heightFactor = fac;
  }

  void setWidthFactor(int fac){
    widthFactor = fac;
  }
  void update(){
    //handle animations in here;
  }

  // These required to being able to handle different sized sprites.

  int heightFactor;
  int widthFactor;

  Texture texture;
};
#endif
