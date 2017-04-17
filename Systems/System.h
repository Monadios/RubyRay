#ifndef SYSTEM_H
#define SYSTEM_H

#include<vector>
#include <typeindex>

#include "../Classes/GameObject.h"
#include "../Components/Component.h"

class System
{
public:
  virtual void update(std::vector<GameObject*>& entities)=0;

  void setRequired(std::vector<Component*> reqs) { required = reqs; }

  bool isCompatibleWith(GameObject* e){
    for(auto it = required.begin(); it != required.end(); it++){
      if( e->components[std::type_index(typeid(it))] == nullptr ){
	return false;
      }
    }
    return true;
  }
private:
  std::vector<Component*> required;
};

#endif
