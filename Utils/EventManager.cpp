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
  std::type_index index = std::type_index(typeid(type));
  //TODO: Fix this. It is a lot of unnecessary operations
  if(subs.find(index) == subs.end()){
    // Not Found
    subs[index] = {obj};
  }else{
    subs[index].push_back(obj);
  }
}

void EventManager::fireEvent(Event e)
{
  for(auto sub : subs[std::type_index(typeid(e))]){
    sub->receive(e);
  }
}

EventManager* EventManager::instance = 0;
