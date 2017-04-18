#ifndef SYSTEM_H
#define SYSTEM_H

#include<vector>
#include <typeindex>
#include<algorithm>

#include "../Classes/GameObject.h"
#include "../Components/Component.h"

class System
{
public:
  void update(std::vector<GameObject*>& entities)
  {
    if(enabled){
      onUpdate(entities);
    }
  }

  virtual void onUpdate(std::vector<GameObject*>& entities)=0;

  void setRequired(std::vector<std::type_index> reqs) { required = reqs; }

  void setEnabled(bool b){ enabled = b; }

  bool isCompatibleWith(GameObject* e){
    return std::any_of(required.begin(), required.end(),
		       [=](std::type_index i){
			 return (e->components.count(i) != 0);
		       });
  }
private:
  std::vector<std::type_index> required;
  bool enabled = true;
};

#endif
