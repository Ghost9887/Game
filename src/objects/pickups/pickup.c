#include "pickup.h"
#include "healthPickup.h"
#include "ammoPickup.h"
#include <string.h>

void drawPickup(Pickup *pickup){
  DrawCircle(pickup->x, pickup->y, 30, pickup->colour);
}

void initPickupArray(Pickup *pickupArr){
  for(int i = 0; i < MAXPICKUPS; i++){
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
  float x = (float)GetRandomValue(0, SCREENWIDTH);
  float y = (float)GetRandomValue(0, SCREENHEIGHT);
    for(int i = 0; i < MAXPICKUPS; i++){
      if(!pickupArr[i].active){
        pickupArr[i] = createHealthPickup(x, y);
        break;
      }
    }
  }
  if(IsKeyPressed(KEY_O)){
    float x = (float)GetRandomValue(0, SCREENWIDTH);
    float y = (float)GetRandomValue(0, SCREENHEIGHT);
    for(int i = 0; i < MAXPICKUPS; i++){
      if(!pickupArr[i].active){
        pickupArr[i] = createAmmoPickup(x, y);
        break;
      }
    }
  }
}

void lifetimeOfPickup(Pickup *pickup){
  if(pickup->lifetime <= 0 && pickup->active){
    pickup->active = false;
  }
  else{
    pickup->lifetime -= GetFrameTime();
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

void updatePickups(Pickup *pickupArr, Player *player){
    spawnPickup(pickupArr);
    for(int i = 0; i < MAXPICKUPS; i++){
      
      //check collision and do appropriate action
      if(pickupArr[i].active){
        if(checkPickupCollisionWithPlayer(&pickupArr[i], player)){
          addPickupData(&pickupArr[i], player);
          pickupArr[i].active = false;
          continue;
        }
        drawPickup(&pickupArr[i]);
      }
      
      //counts down the pickup lifetime or destroys it
      lifetimeOfPickup(&pickupArr[i]);
    }
}

