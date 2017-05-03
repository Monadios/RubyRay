#ifndef EVENT_H
#define EVENT_H

#include<string>

class Event
{
public:
  Event()=default;
  ~Event()=default;
  virtual std::string getName()=0;
  const std::string name;
};

#endif
