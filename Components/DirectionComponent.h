#include "../Components/Component.h"

class DirectionComponent : public Component
{
public:
  DirectionComponent(double dx, double dy) : x(dx), y(dy) {};
  void sendMessage( Msg msg ) {};
  double x;
  double y;
};
