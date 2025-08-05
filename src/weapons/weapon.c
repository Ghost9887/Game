#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "raylib.h"
#include "rocketLauncher.h"

void drawWeapon(Player *player) {
  DrawRectangle(player->x, player->y, player->weapon.width, player->weapon.height, BLACK);
}

// refactor this
void initWeaponArr(Weapon *weaponArr) {
  weaponArr[0] = createPistol();
  weaponArr[1] = createAssaultRifle();
  weaponArr[2] = createRocketLauncher();
  for (int i = 3; i < 10; i++) {
    weaponArr[i] = createPistol();
  }
}

// REFACTOR
void switchWeapons(Player *player, Weapon *weaponArr) {
  if (IsKeyPressed(KEY_ONE)) {
    weaponArr[0].holding = true;
    weaponArr[1].holding = false;
    weaponArr[2].holding = false;
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_TWO)) {
    weaponArr[1].holding = true;
    weaponArr[0].holding = false;
    weaponArr[2].holding = false;
    player->timer = 1.0f * (float)TARGETFPS;
  } else if (IsKeyPressed(KEY_THREE)) {
    weaponArr[2].holding = true;
    weaponArr[1].holding = false;
    weaponArr[0].holding = false;
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
