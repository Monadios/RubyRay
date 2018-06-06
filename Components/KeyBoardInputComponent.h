#ifndef KEYBOARDINPUTCOMPONENT_H
#define KEYBOARDINPUTCOMPONENT_H

class Player;

#include <SDL/SDL.h>
#include <iostream>
#include <memory>

#include "../Components/Component.h"
#include "../Classes/GameObject.h"
#include "../Utils/Camera.h"
#include "../Utils/quickcg.h"

class KeyBoardInputComponent : public Component
{
public:
  KeyBoardInputComponent(std::vector<std::vector<int>>& map ) : worldMap(map) {}

  ~KeyBoardInputComponent() = default;
  void sendMessage( Msg msg ) {};
  std::vector<std::vector<int>>& worldMap;
};

#endif
