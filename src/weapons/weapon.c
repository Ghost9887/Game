#include "weapon.h"
#include "assaultRifle.h"
#include "pistol.h"
#include "raylib.h"
#include "rocketLauncher.h"

extern const unsigned int TARGETFPS;

void drawWeapon(Player *player, Weapon *weapon) {
  DrawRectangle(player->x, player->y, weapon->width, weapon->height, BLACK);
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
