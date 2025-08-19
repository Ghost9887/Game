#include "assaultRifle.h"

Weapon createAssaultRifle() {
  Weapon assualtRifle;
  assualtRifle.id = 1;
  assualtRifle.x = 0;
  assualtRifle.y = 0;
  assualtRifle.scale = 1.7f;
  assualtRifle.spread = 10;
  assualtRifle.width = 32 * assualtRifle.scale;
  assualtRifle.height = 32 * assualtRifle.scale;
  assualtRifle.range = 750.0f;
  assualtRifle.damage = 70.0f;
  assualtRifle.maxMagSize = 30;
  assualtRifle.currentMagSize = assualtRifle.maxMagSize;
  assualtRifle.maxReserveSize = 150;
  assualtRifle.currentReserveSize = assualtRifle.maxReserveSize;
  assualtRifle.reloadTime = 2.8f;
  assualtRifle.reloadTimer = 0.0f;
  assualtRifle.type = "ballistic";
  assualtRifle.name = "M4";
  assualtRifle.fireRate = 0.3 * (float)TARGETFPS;
  assualtRifle.projectileSpeed = 3000.0f;
  assualtRifle.weaponCost = 0;
  assualtRifle.ammoCost = 100;
  assualtRifle.weight = 0.9f;
   //animations
  assualtRifle.currentFrame = 0;
  assualtRifle.frameTime = 0.0f;
  assualtRifle.frameSpeed = 0.1f; // seconds per frame
  // used for selecting the coordinates on the sprite sheet
  assualtRifle.frameRec = (Rectangle){ 0.0f, 0.0f, 32.0f, 32.0f};
  return assualtRifle;
}
