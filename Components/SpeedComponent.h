#include "../Components/Component.h"

class SpeedComponent : public Component
{
public:
  SpeedComponent(double rot, double move,
		 double rf, double mf) : rotSpeed(rot), moveSpeed(move),
					 rotFac(rf), movFac(mf) {};
  inline void update() {}

  double rotSpeed;
  double moveSpeed;
  double rotFac;
  double movFac;
};
