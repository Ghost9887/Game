#include "pistol.h"
#include <stdbool.h>

Weapon createPistol() {
  Weapon pistol;
  pistol.id = 0;
  pistol.x = 0;
  pistol.y = 0;
  pistol.scale = 1.0f;
  pistol.width = 32 * pistol.scale;
  pistol.height = 32 * pistol.scale;
  pistol.damage = 30.0f;
  pistol.maxMagSize = 6;
  pistol.maxReserveSize = 42; //should always be divisible by the mag size
  pistol.currentMagSize = pistol.maxMagSize;
  pistol.currentReserveSize = pistol.maxReserveSize;
  pistol.reloadTime = 2.2f;
  pistol.reloadTimer = 0.0f;
  pistol.type = "ballistic";
  pistol.name = "1911";
  pistol.range = 350.0f;
  pistol.projectileSpeed = 1250.0f;
  pistol.fireRate =
      0.70f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  pistol.weaponCost = 0;
  pistol.ammoCost = 150;
  return pistol;
}

