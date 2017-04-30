#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include<vector>
#include<map>
#include "../Events/Event.h"
#include "../Classes/GameObject.h"

class EventManager
{
  static EventManager* instance;
public:
  void subscribe(GameObject* obj, Event type);
  static EventManager* getInstance();
private:
  std::map<GameObject*, Event> subs;
};

#endif
