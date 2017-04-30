#include "../Utils/EventManager.h"

EventManager* EventManager::getInstance()
{
  if(!instance){
    instance = new EventManager;
  }
  return instance;
}

void EventManager::subscribe(GameObject* obj, Event type)
{
  subs.insert(std::map<GameObject*, Event>::value_type(obj,type));
}

EventManager* EventManager::instance  =  0;
