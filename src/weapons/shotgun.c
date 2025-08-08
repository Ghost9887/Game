#include "shotgun.h"


Weapon createShotgun(){
  Weapon shotgun;
  shotgun.x = 0;
  shotgun.y = 0;
  shotgun.width = 50;
  shotgun.height = 20;
  shotgun.damage = 100.0f;
  shotgun.maxMagSize = 4;
  shotgun.maxReserveSize = 24; //should always be divisible by the mag size
  shotgun.currentMagSize = shotgun.maxMagSize;
  shotgun.currentReserveSize = shotgun.maxReserveSize;
  shotgun.reloadTime = 2.2f;
  shotgun.reloadTimer = 0.0f;
  shotgun.type = "ballistic";
  shotgun.range = 350.0f;
  shotgun.projectileSpeed = 1250.0f;
  shotgun.fireRate =
      1.2f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  shotgun.holding = true;
  return shotgun;
}
