#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "raylib.h"
#include "rocketLauncher.h"
#include "smg.h"
#include "shotgun.h"
#include <math.h>

const unsigned int numOfWeapons = 5;

void drawWeapon(Player *player) {
  Rectangle weaponRect = {
    player->x + player->width / 2.0f,
    player->y + player->height / 2.0f,
    player->weapon->width,
    player->weapon->height
  };

  Vector2 pivot = {player->weapon->width / 2.0f, player->weapon->height / 2.0f};
  float rotation = getRotationOfWeapon(player);
  player->weapon->rotation = rotation;
  DrawRectanglePro(weaponRect, pivot, rotation, BLACK);
}

//initialize the array with all the weapons
void initWeaponArr(Weapon *weaponArr) {
  weaponArr[0] = createPistol();
  weaponArr[1] = createAssaultRifle();
  weaponArr[2] = createRocketLauncher();
  weaponArr[3] = createSMG();
  weaponArr[4] = createShotgun();
  // creates the weapons that don't exist yet so the array doesnt have random
  // data
}


void initWeaponHolster(int *weaponHolster, Weapon *weaponArr){
  weaponHolster[0] = weaponArr[0].id;
  weaponHolster[1] = weaponArr[3].id; 
  weaponHolster[2] = -1;
}

float getRotationOfWeapon(Player *player){
  Vector2 mousePosition = GetMousePosition();
  float rad = atan2(mousePosition.y - player->y, mousePosition.x - player->x);
  float degree = rad * (180.0f / 3.14);
  return degree;
}

bool isReloading(Weapon *weapon){
  if(weapon->reloadTimer > 0.0f){
    return true;
  }
  return false;
}

void checkReload(Weapon *weapon, Player *player) {
  //only call when a reload gets initiated
  //MAYBE CHANGE TO AFFECT THE PLAYER TIMER INSTEAD OF HAVING A SPERATE RELOAD TIMER?
  if(IsKeyPressed(KEY_R) || weapon->reloadTimer > 0.0f || weapon->currentMagSize <= 0){
   if (weapon->currentReserveSize > 0 && weapon->currentMagSize < weapon->maxMagSize) {
      if (weapon->reloadTimer <= 0.0f) {
        weapon->reloadTimer = weapon->reloadTime;
      } else {
        weapon->reloadTimer -= GetFrameTime();
        if (weapon->reloadTimer <= 0.0f) {
          int ammoToLoad = weapon->maxMagSize - weapon->currentMagSize;
          if (weapon->currentReserveSize < ammoToLoad) {
            ammoToLoad = weapon->currentReserveSize;
          }
          weapon->currentMagSize += ammoToLoad;
          weapon->currentReserveSize -= ammoToLoad;
          weapon->reloadTimer = 0.0f;
        }
      }
    }
  }
}


void reduceAmmo(Weapon *weapon){
  weapon->currentMagSize -= 1;
}

int getMagAmmo(Weapon *weapon){
  return weapon->currentMagSize;
}

int getReserveAmmo(Weapon *weapon){
  return weapon->currentReserveSize;
}

void switchWeapons(Player *player, int *weaponHolster, Weapon *weaponArr) {
  if(IsKeyPressed(KEY_ONE)){
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    int id = weaponHolster[0];
    //check if we have a weapon in that slot
    if(id != -1){
      player->weapon->holding = false;
      for(int i = 0; i < numOfWeapons; i++){
        if(weaponArr[i].id == id){
          player->weapon = &weaponArr[i];
          weaponArr[i].holding = true;
        }
      }
    }
  }
  else if(IsKeyPressed(KEY_TWO)){
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    int id = weaponHolster[1];
    if(id != -1){
      player->weapon->holding = false;
      for(int i = 0; i < numOfWeapons; i++){
        if(weaponArr[i].id == id){
          player->weapon = &weaponArr[i];
          weaponArr[i].holding = true;
        }
      }
    }
  }
  else if(IsKeyPressed(KEY_THREE)){
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    int id = weaponHolster[2];
    if(id != -1){
      player->weapon->holding = false;
      for(int i = 0; i < numOfWeapons; i++){
        if(weaponArr[i].id == id){
          player->weapon = &weaponArr[i];
          weaponArr[i].holding = true;
        }
      }
    }
  }
}

void replaceWeapon(Weapon *weapon, Player *player){
  player->weapon->holding = false;
  player->weapon = weapon;
  weapon->holding = true;
}

void replenishAmmo(Player *player, Weapon *weapon) {
  weapon->currentMagSize = weapon->maxMagSize; 
  weapon->currentReserveSize = weapon->maxReserveSize;
}

void updateWeapon(Weapon *weaponArr, Player *player, int *weaponHolster) {
  player->weapon->x = player->x;
  player->weapon->y = player->y;
  drawWeapon(player);
  switchWeapons(player, weaponHolster, weaponArr); // listens if the player has switched
  checkReload(player->weapon, player);
}
