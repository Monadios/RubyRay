#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include<vector>
#include<map>
#include<typeindex>
#include "../Events/Event.h"
#include "../Classes/GameObject.h"

class EventManager
{
  static EventManager* instance;
public:
  void subscribe(GameObject* obj, Event type);
  static EventManager* getInstance();
  void fireEvent(Event e);
private:
  std::map<std::type_index, std::vector<GameObject*>> subs;
};

#endif
