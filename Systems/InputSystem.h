#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

class Player;

#include <SDL/SDL.h>
#include <iostream>
#include <memory>

#include "../Systems/System.h"
#include "../Classes/GameObject.h"
#include "../Utils/Camera.h"
#include "../Utils/quickcg.h"

class InputSystem : public System
{
public:
  InputSystem() = default;
  ~InputSystem() = default;

  void update(std::vector<GameObject*>& entities);
  Uint8* keyboard;

private:
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame
};

#endif
