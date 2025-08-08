#include "pickup.h"
#include "healthPickup.h"
#include "ammoPickup.h"
#include <string.h>

void drawPickup(Pickup *pickup){
  DrawCircle(pickup->x, pickup->y, 30, pickup->colour);
}

void initPickupArray(Pickup *pickupArr){
  for(int i = 2; i < MAXPICKUPS; i++){
    Pickup pickup;
    pickup.x = 0;
    pickup.y = 0;
    pickup.colour;
    pickup.active = false;
    pickup.lifetime = 0.0f;
    pickupArr[i] = pickup;
  }
}

void spawnPickup(Pickup *pickupArr){
  if(IsKeyPressed(KEY_H)){
    pickupArr[0] = createHealthPickup();
  }
  if(IsKeyPressed(KEY_O)){
    pickupArr[1] = createAmmoPickup();
  }
}

void updatePickups(Pickup *pickupArr, Player *player){
    spawnPickup(pickupArr);
    for(int i = 0; i < MAXPICKUPS; i++){
      if(pickupArr[i].active){
        if(checkPickupCollisionWithPlayer(&pickupArr[i], player)){
          addPickupData(&pickupArr[i], player);
          pickupArr[i].active = false;
          continue;
        }
        drawPickup(&pickupArr[i]);
      }
    }
}

void addPickupData(Pickup *pickup, Player *player){
  if(strcmp(pickup->type, "health") == 0){
    if(player->health + pickup->data >= 100){
      player->health = 100;
    }else{
      player->health += pickup->data;
    }
  }else if(strcmp(pickup->type, "ammo") == 0){
    if(player->weapon->currentReserveSize + pickup->data >= player->weapon->maxReserveSize){
      player->weapon->currentReserveSize = player->weapon->maxReserveSize;
    }else{
      player->weapon->currentReserveSize += pickup->data;
    }
  }
}

bool checkPickupCollisionWithPlayer(Pickup *pickup, Player *player){
   Rectangle playerRect = {player->x, player->y, player->width, player->height};
    return CheckCollisionCircleRec((Vector2){pickup->x, pickup->y},30, playerRect);
}

