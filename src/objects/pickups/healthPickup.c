#include "healthPickup.h"


Pickup createHealthPickup(float x, float y){
  Pickup healthPickup;
  healthPickup.x = x;
  healthPickup.y = y;
  healthPickup.data = 20;
  healthPickup.colour = GREEN;
  healthPickup.active = true;
  healthPickup.lifetime = 10.0f;
  healthPickup.type = "health";
  return healthPickup;
}
