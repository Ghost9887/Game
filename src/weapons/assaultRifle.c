#include "assaultRifle.h"

Weapon createAssaultRifle() {
  Weapon assualtRifle;
  assualtRifle.x = 0;
  assualtRifle.y = 0;
  assualtRifle.width = 40;
  assualtRifle.height = 10;
  assualtRifle.range = 750.0f;
  assualtRifle.damage = 70.0f;
  assualtRifle.type = "ballistic";
  assualtRifle.fireRate = 0.2 * (float)TARGETFPS;
  assualtRifle.holding = false;
  return assualtRifle;
}
