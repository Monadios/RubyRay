#ifndef EVENT_H
#define EVENT_H

#include<string>

class Event
{
public:
  Event(std::string eventName) : name(eventName) {}
  std::string getName();
private:
  const std::string name;
};

#endif
