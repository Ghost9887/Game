#ifndef PICKUP_H
#define PICKUP_H

#include "raylib.h"
#include "common.h"
  
  void drawPickup(Pickup *pickup);
  void initPickupArray(Pickup *pickupArr);
  void updatePickups(Pickup *pickupArr, Player *player);
  void spawnPickup(Pickup *pickupArr, float x, float y, char *type);
  bool checkPickupCollisionWithPlayer(Pickup *pickup, Player *player);
  void addPickupData(Pickup *pickup, Player *player);
  void lifetimeOfPickup(Pickup *pickup);

#endif
