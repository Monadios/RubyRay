#include "../Components/Component.h"

class PositionComponent : public Component
{
public:
  PositionComponent(double _x, double _y) : x(_x), y(_y) {};
  void sendMessage( Msg msg ) {};

  double x;
  double y;
};
