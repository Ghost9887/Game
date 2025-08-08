#ifndef PICKUP_H
#define PICKUP_H

#include "raylib.h"
#include "common.h"
  
  void drawPickup(Pickup *pickup);
  void initPickupArray(Pickup *pickupArr);
  void updatePickups(Pickup *pickupArr);

#endif
