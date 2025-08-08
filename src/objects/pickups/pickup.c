#include "pickup.h"
#include "healthPickup.h"
#include "ammoPickup.h"

void drawPickup(Pickup *pickup){
  DrawCircle(pickup->x, pickup->y, 30, pickup->colour);
}

void initPickupArray(Pickup *pickupArr){
  pickupArr[0] = createHealthPickup();
  pickupArr[1] = createAmmoPickup();
  for(int i = 2; i < MAXPICKUPS; i++){
    pickupArr[i] = createHealthPickup();
  }
}

void updatePickups(Pickup *pickupArr){
    drawPickup(&pickupArr[0]);
    drawPickup(&pickupArr[1]);
}

