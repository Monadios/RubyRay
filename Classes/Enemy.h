#include "../Classes/GameObject.h"

class TextureComponent;

#include "../Components/TextureComponent.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public GameObject
{
public:
  Enemy(double x, double y);
  void update();
};

#endif
