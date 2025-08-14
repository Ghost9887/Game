#include "shotgun.h"
#include "projectile.h"


Weapon createShotgun(){
  Weapon shotgun;
  shotgun.id = 3;
  shotgun.x = 0;
  shotgun.y = 0;
  shotgun.width = 50;
  shotgun.height = 20;
  shotgun.damage = 25.0f;
  shotgun.maxMagSize = 4;
  shotgun.maxReserveSize = 24; //should always be divisible by the mag size
  shotgun.currentMagSize = shotgun.maxMagSize;
  shotgun.currentReserveSize = shotgun.maxReserveSize;
  shotgun.reloadTime = 2.2f;
  shotgun.reloadTimer = 0.0f;
  shotgun.type = "spreadshot";
  shotgun.range = 350.0f;
  shotgun.projectileSpeed = 1250.0f;
  shotgun.fireRate =
      1.2f *
      (float)TARGETFPS; // 1.0f == every second ; 0.5 == every 1/2 second
  shotgun.weaponCost = 1800;
  shotgun.ammoCost = 1000;
  shotgun.holding = true;
  return shotgun;
}

void spreadShot(Projectile *projectileArr, Player *player) {
    float spreadAngle = 5.0f; 
    int shots = 5;
    int center = shots / 2;
    for (int i = 0; i < shots; i++) {
        float angleOffset = (i - center) * spreadAngle;
        for (int j = 0; j < MAXPROJECTILES; j++) {
            if (!projectileArr[j].active) {
                projectileArr[j] = createProjectile(player, player->weapon, angleOffset);
                break;
            }
        }
    }
}


