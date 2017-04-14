#include "../Components/Component.h"

class DirectionComponent : public Component
{
public:
  DirectionComponent(double dx, double dy) : x(dx), y(dy) {};
  inline void update() {}

  double x;
  double y;
};
