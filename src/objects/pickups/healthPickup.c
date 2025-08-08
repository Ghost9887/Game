#include "healthPickup.h"


Pickup createHealthPickup(){
  Pickup healthPickup;
  healthPickup.x = 600;
  healthPickup.y = 600;
  healthPickup.data = 20;
  healthPickup.colour = GREEN;
  return healthPickup;
}
