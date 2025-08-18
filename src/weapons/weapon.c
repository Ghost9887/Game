#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "raylib.h"
#include "rocketLauncher.h"
#include "smg.h"
#include "shotgun.h"
#include "lmg.h"
#include <math.h>

extern unsigned int AMOUNTOFWEAPONS;

void loadWeaponTextures(Texture2D *weaponTextureArr){
  //they match the id of the weapon so that we cant just grab them without looking (same with the enemy)
  weaponTextureArr[0] = LoadTexture("assets/weapons/pistol/pistol.png");
  weaponTextureArr[1] = LoadTexture("assets/weapons/ar/ar.png");
  weaponTextureArr[2] = LoadTexture("assets/weapons/rpg/rpg.png");
  weaponTextureArr[3] = LoadTexture("assets/weapons/shotgun/shotgun.png");
  weaponTextureArr[4] = LoadTexture("assets/weapons/smg/smg.png");
  weaponTextureArr[5] = LoadTexture("assets/weapons/rpg/rpg.png");
}

void drawWeapon(Player *player, Texture2D *weaponTextureArr) {
    float scale = player->weapon->scale;  
    float rotation = getRotationOfWeapon(player);
    Rectangle source = { 0, 0, weaponTextureArr[player->weapon->id].width, 
                            weaponTextureArr[player->weapon->id].height };
    //flips the gun depending on which side its on
    if (rotation > 90.0f || rotation < -90.0f) {
      source.height *= -1;
    }
    Rectangle dest = {
        player->x + player->width / 2,
        player->y + player->height / 2 + 20,
        weaponTextureArr[player->weapon->id].width * scale,
        weaponTextureArr[player->weapon->id].height * scale,
    };
    Vector2 pivot = {player->weapon->width / 2.0f, player->weapon->height / 2.0f};
    player->weapon->rotation = rotation;
    DrawTexturePro(weaponTextureArr[player->weapon->id], source, dest, pivot, rotation, WHITE);
}


//initialize the array with all the weapons
void initWeaponArr(Weapon *weaponArr) {
  weaponArr[0] = createPistol();
  weaponArr[1] = createAssaultRifle();
  weaponArr[2] = createRocketLauncher();
  weaponArr[3] = createSMG();
  weaponArr[4] = createShotgun();
  weaponArr[5] = createLmg();
}


void initWeaponHolster(int *weaponHolster, Weapon *weaponArr){
  weaponHolster[0] = weaponArr[0].id;
  weaponHolster[1] = -1; 
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
  if(IsKeyPressed(KEY_R) || isReloading(weapon) || weapon->currentMagSize <= 0){
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
      for(int i = 0; i < AMOUNTOFWEAPONS; i++){
        if(weaponArr[i].id == id){
          player->weapon = &weaponArr[i];
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
      for(int i = 0; i < AMOUNTOFWEAPONS; i++){
        if(weaponArr[i].id == id){
          player->weapon = &weaponArr[i];
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
      for(int i = 0; i < AMOUNTOFWEAPONS; i++){
        if(weaponArr[i].id == id){
          player->weapon = &weaponArr[i];
        }
      }
    }
  }
}

//when buying a gun
void replaceWeapon(Weapon *weapon, Player *player){
  player->weapon = weapon;
}

//when buying a gun(and the gun is already in the player holster)
void replenishAmmo(Player *player, Weapon *weapon) {
  weapon->currentReserveSize = weapon->maxReserveSize;
  //fixes the bug where buying the ammo while reloading would make the gun not shoot
  weapon->reloadTimer = 0.0f;
}

void updateWeapon(Weapon *weaponArr, Player *player, int *weaponHolster, Texture2D *weaponTextureArr) {
  player->weapon->x = player->x;
  player->weapon->y = player->y;
  drawWeapon(player, weaponTextureArr);
  switchWeapons(player, weaponHolster, weaponArr); // listens if the player has switched
  checkReload(player->weapon, player);
}
