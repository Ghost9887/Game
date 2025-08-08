#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "raylib.h"
#include "rocketLauncher.h"
#include "smg.h"

typedef enum { PISTOL = 0, AR = 1, ROCKETLAUNCER = 2, SMG = 3 } WeaponHolding;

// create the enums objects
WeaponHolding pistol = PISTOL;
WeaponHolding ar = AR;
WeaponHolding rocketLauncher = ROCKETLAUNCER;
WeaponHolding smg = SMG;

const unsigned int numOfWeapons = 4;

void drawWeapon(Player *player) {
  DrawRectangle(player->x, player->y, player->weapon->width,
                player->weapon->height, BLACK);
}

// refactor this
void initWeaponArr(Weapon *weaponArr) {
  weaponArr[pistol] = createPistol();
  weaponArr[ar] = createAssaultRifle();
  weaponArr[rocketLauncher] = createRocketLauncher();
  weaponArr[smg] = createSMG();
  // creates the weapons that don't exist yet so the array doesnt have random
  // data
  for (int i = 4; i < 10; i++) {
    // place holder
    weaponArr[i] = createPistol();
  }
}

bool isReloading(Weapon *weapon){
  if(weapon->reloadTimer > 0.0f){
    return true;
  }
  return false;
}

void checkReload(Weapon *weapon, Player *player) {
  //only call when a reload gets initiated
  if(IsKeyPressed(KEY_R) || weapon->reloadTimer > 0.0f || weapon->currentMagSize <= 0){
    isReloading(weapon);
    if (weapon->currentReserveSize > 0 && weapon->currentMagSize < weapon->maxMagSize) {
      if (weapon->reloadTimer <= 0.0f) {
        weapon->reloadTimer = weapon->reloadTime;
        player->canShoot = false;
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
          player->canShoot = true;
          isReloading(weapon);
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

// REFACTOR
void switchWeapons(Player *player, Weapon *weaponArr) {
  if (IsKeyPressed(KEY_ONE)) {
    //cancel reload
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    for (int i = 0; i < numOfWeapons; i++) {
      if (i == pistol) {
        weaponArr[i].holding = true;
      } else {
        weaponArr[i].holding = false;
      }
    }
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_TWO)) {
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    for (int i = 0; i < numOfWeapons; i++) {
      if (i == ar) {
        weaponArr[i].holding = true;
      } else {
        weaponArr[i].holding = false;
      }
    }
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_THREE)) {
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    for (int i = 0; i < numOfWeapons; i++) {
      if (i == rocketLauncher) {
        weaponArr[i].holding = true;
      } else {
        weaponArr[i].holding = false;
      }
    }
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_FOUR)) {
    if(isReloading(player->weapon)){
      player->weapon->reloadTimer = 0.0f;
    }
    for (int i = 0; i < numOfWeapons; i++) {
      if (i == smg) {
        weaponArr[i].holding = true;
      } else {
        weaponArr[i].holding = false;
      }
    }
    //maybe change this???
    player->timer = 1.0f * (float)TARGETFPS;
  }
}

void updateWeapon(Weapon *weaponArr, Player *player) {
  int index;
  for (index = 0; index < 10; index++) {
    if (weaponArr[index].holding == true)
      break;
  }
  player->weapon = &weaponArr[index];
  weaponArr[index].x = player->x;
  weaponArr[index].y = player->y;
  drawWeapon(player);
  switchWeapons(player, weaponArr); // listens if the player has switched
  checkReload(&weaponArr[index], player);
}
