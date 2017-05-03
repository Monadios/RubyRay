#ifndef PLAYER_SHOOT_EVENT_H
#define PLAYER_SHOOT_EVENT_H

#include<string>
#include "../Events/Event.h"

class PlayerShootEvent : public Event
{
public:
  int x, y;
  PlayerShootEvent(int x_, int y_) : x(x_), y(y_) {}
  std::string getName() {
    return "PlayerShootEvent";
  }
};

#endif
