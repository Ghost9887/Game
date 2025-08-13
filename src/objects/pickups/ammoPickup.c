#include "ammoPickup.h"

Pickup createAmmoPickup(float x, float y, Player *player){
  Pickup ammoPickup;
  ammoPickup.x = x;
  ammoPickup.y = y;
  ammoPickup.data = player->weapon->maxMagSize * 2;
  ammoPickup.colour = YELLOW;
  ammoPickup.active = true;
  ammoPickup.lifetime = 10.0f;
  ammoPickup.type = "ammo";
  return ammoPickup;
}
