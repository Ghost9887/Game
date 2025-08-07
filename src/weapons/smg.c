#include "smg.h"
#include <stdbool.h>

Weapon createSMG() {
  Weapon smg;
  smg.x = 0;
  smg.y = 0;
  smg.width = 30;
  smg.height = 10;
  smg.damage = 20.0f;
  smg.type = "ballistic";
  smg.range = 250.0f;
  smg.projectileSpeed = 1700.0f;
  smg.fireRate =
      0.10f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  smg.holding = true;
  return smg;
}
