#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "smg.h"
#include "raylib.h"
#include "rocketLauncher.h"

typedef enum{
  PISTOL = 0,
  AR = 1,
  ROCKETLAUNCER = 2,
  SMG = 3
}WeaponHolding;

//create the enums objects
WeaponHolding pistol = PISTOL;
WeaponHolding ar = AR;
WeaponHolding rocketLauncher = ROCKETLAUNCER;
WeaponHolding smg = SMG;

const unsigned int numOfWeapons = 4;

void drawWeapon(Player *player) {
  DrawRectangle(player->x, player->y, player->weapon.width, player->weapon.height, BLACK);
}

// refactor this
void initWeaponArr(Weapon *weaponArr) {
  weaponArr[pistol] = createPistol();
  weaponArr[ar] = createAssaultRifle();
  weaponArr[rocketLauncher] = createRocketLauncher();
  weaponArr[smg] = createSMG(); 
  //creates the weapons that don't exist yet so the array doesnt have random data 
  for (int i = 4; i < 10; i++) {
    //place holder
    weaponArr[i] = createPistol();
  }
}

// REFACTOR
void switchWeapons(Player *player, Weapon *weaponArr) {
  if (IsKeyPressed(KEY_ONE)) {
    for(int i = 0; i < numOfWeapons; i++){
      if(i == pistol){
        weaponArr[i].holding = true;
      }else{
        weaponArr[i].holding = false;
      }
    }
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_TWO)) {
    for(int i = 0; i < numOfWeapons; i++){
      if(i == ar){
        weaponArr[i].holding = true;
      }else{
        weaponArr[i].holding = false;
      }
    }
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_THREE)) {
     for(int i = 0; i < numOfWeapons; i++){
      if(i == rocketLauncher){
        weaponArr[i].holding = true;
      }else{
        weaponArr[i].holding = false;
      }
    }
    player->timer = 1.0f * (float)TARGETFPS;
  }else if(IsKeyPressed(KEY_FOUR)){
    for(int i = 0; i < numOfWeapons; i++){
      if(i == smg){
        weaponArr[i].holding = true;
      }else{
        weaponArr[i].holding = false;
      }
    }   
    player->timer = 1.0f * (float)TARGETFPS;
  }
}

void updateWeapon(Weapon *weaponArr, Player *player) {
  int index;
  for (index = 0; index < 10; index++) {
    if (weaponArr[index].holding == true)
      break;
  }
  player->weapon = weaponArr[index];
  weaponArr[index].x = player->x;
  weaponArr[index].y = player->y;
  drawWeapon(player);
  switchWeapons(player, weaponArr); // listens if the player has switched
}
