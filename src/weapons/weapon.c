#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "raylib.h"
#include "rocketLauncher.h"

typedef enum{
  PISTOL = 0,
  AR = 1,
  ROCKETLAUNCER = 2
}WeaponHolding;

WeaponHolding pistol = PISTOL;
WeaponHolding ar = AR;
WeaponHolding rocketLauncher = ROCKETLAUNCER;

void drawWeapon(Player *player) {
  DrawRectangle(player->x, player->y, player->weapon.width, player->weapon.height, BLACK);
}

// refactor this
void initWeaponArr(Weapon *weaponArr) {
  weaponArr[pistol] = createPistol();
  weaponArr[ar] = createAssaultRifle();
  weaponArr[rocketLauncher] = createRocketLauncher();
  for (int i = 3; i < 10; i++) {
    weaponArr[i] = createPistol();
  }
}

// REFACTOR
void switchWeapons(Player *player, Weapon *weaponArr) {
  if (IsKeyPressed(KEY_ONE)) {
    weaponArr[pistol].holding = true;
    weaponArr[ar].holding = false;
    weaponArr[rocketLauncher].holding = false;
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_TWO)) {
    weaponArr[ar].holding = true;
    weaponArr[pistol].holding = false;
    weaponArr[rocketLauncher].holding = false;
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_THREE)) {
    weaponArr[rocketLauncher].holding = true;
    weaponArr[ar].holding = false;
    weaponArr[pistol].holding = false;
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
