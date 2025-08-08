#include "ammoPickup.h"

Pickup createAmmoPickup(){
  Pickup ammoPickup;
  ammoPickup.x = 700;
  ammoPickup.y = 700;
  ammoPickup.data = 10;
  ammoPickup.colour = YELLOW;
  ammoPickup.active = true;
  ammoPickup.lifetime = 10.0f;
  ammoPickup.type = "ammo";
  return ammoPickup;
}
