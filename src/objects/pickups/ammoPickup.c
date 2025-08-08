#include "ammoPickup.h"

Pickup createAmmoPickup(){
  Pickup ammoPickup;
  ammoPickup.x = 700;
  ammoPickup.y = 700;
  ammoPickup.data = 10;
  ammoPickup.colour = YELLOW;
  return ammoPickup;
}
