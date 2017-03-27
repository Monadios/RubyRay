#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "../Utils/Texture.h"
#include "../Classes/Component.h"

class TextureComponent : public Component
{
public:
  TextureComponent(Texture* tex);
  void update(){
    ;
  }
private:
  Texture* tex;
};
#endif
