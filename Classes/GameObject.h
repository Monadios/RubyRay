#include "./Player.h"

struct GameObject
{
  double x;
  double y;
  int texture;

  virtual void update(Player* p)=0;
};
