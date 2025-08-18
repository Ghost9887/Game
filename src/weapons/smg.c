#include "smg.h"
#include <stdbool.h>

Weapon createSMG() {
  Weapon smg;
  smg.id = 4;
  smg.x = 0;
  smg.y = 0;
  smg.scale = 1.0f;
  smg.spread = 20;
  smg.width = 32 * smg.scale;
  smg.height = 32 * smg.scale;
  smg.damage = 200.0f;
  smg.maxMagSize = 4000;
  smg.currentMagSize = smg.maxMagSize;
  smg.maxReserveSize = 240;
  smg.currentReserveSize = smg.maxReserveSize;
  smg.reloadTime = 2.0f;
  smg.reloadTimer = 0.0f;
  smg.type = "ballistic";
  smg.name = "Vector";
  smg.range = 350.0f;
  smg.projectileSpeed = 1700.0f;
  smg.fireRate =
      0.05f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  smg.weaponCost = 0;
  smg.ammoCost = 100;
  smg.weight = 1.0f;
  return smg;
}
