#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "../Utils/Texture.h"
#include "../Classes/Component.h"

class TextureComponent : public Component
{
public:
  TextureComponent(Texture* tex);
  void update(){
    //handle animations in here;
  }

  // These required to being able to handle different sized sprites.

  int heightFactor;
  int widthFactor;

private:
  Texture* tex;
};
#endif
