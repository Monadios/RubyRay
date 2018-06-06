#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Classes/Msg.h"

class Component
{
public:
  virtual void sendMessage( Msg msg )=0;
};

#endif
