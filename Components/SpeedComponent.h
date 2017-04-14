#include "../Components/Component.h"

class SpeedComponent : public Component
{
public:
  SpeedComponent(double rot, double move) : rotSpeed(rot), moveSpeed(move) {};
  inline void update() {}

  double rotSpeed;
  double moveSpeed;
};
