#include "assaultRifle.h"

Weapon createAssaultRifle() {
  Weapon assualtRifle;
  assualtRifle.x = 0;
  assualtRifle.y = 0;
  assualtRifle.width = 40;
  assualtRifle.height = 10;
  assualtRifle.range = 750.0f;
  assualtRifle.damage = 70.0f;
  assualtRifle.maxMagSize = 30;
  assualtRifle.currentMagSize = assualtRifle.maxMagSize;
  assualtRifle.maxReserveSize = 150;
  assualtRifle.currentReserveSize = assualtRifle.maxReserveSize;
  assualtRifle.reloadTime = 2.8f;
  assualtRifle.reloadTimer = 0.0f;
  assualtRifle.type = "ballistic";
  assualtRifle.fireRate = 0.3 * (float)TARGETFPS;
  assualtRifle.projectileSpeed = 3000.0f;
  assualtRifle.holding = false;
  return assualtRifle;
}
