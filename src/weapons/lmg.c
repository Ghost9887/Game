#include "lmg.h"
#include <stdbool.h>

Weapon createLmg() {
  Weapon lmg;
  lmg.id = 5;
  lmg.x = 0;
  lmg.y = 0;
  lmg.scale = 1.0f;
  lmg.spread = 20;
  lmg.width = 32 * lmg.scale;
  lmg.height = 32 * lmg.scale;
  lmg.damage = 45.0f;
  lmg.maxMagSize = 100;
  lmg.maxReserveSize = 300; //should always be divisible by the mag size
  lmg.currentMagSize = lmg.maxMagSize;
  lmg.currentReserveSize = lmg.maxReserveSize;
  lmg.reloadTime = 4.2f;
  lmg.reloadTimer = 0.0f;
  lmg.type = "ballistic";
  lmg.name = "M42";
  lmg.range = 650.0f;
  lmg.projectileSpeed = 1250.0f;
  lmg.fireRate =
      0.03f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  lmg.weaponCost = 0;
  lmg.ammoCost = 150;
  lmg.weight = 0.5f;
  return lmg;
}

