#include "pistol.h"
#include <stdbool.h>

Weapon createPistol() {
  Weapon pistol;
  pistol.x = 0;
  pistol.y = 0;
  pistol.width = 20;
  pistol.height = 10;
  pistol.damage = 40.0f;
  pistol.type = "ballistic";
  pistol.range = 350.0f;
  pistol.projectileSpeed = 1250.0f;
  pistol.fireRate =
      0.70f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  pistol.holding = true;
  return pistol;
}
