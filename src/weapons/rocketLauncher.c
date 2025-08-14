#include "rocketLauncher.h"
#include "enemy.h"
#include "projectile.h"
#include "common.h"
#include <math.h>

Weapon createRocketLauncher() {
  Weapon rocketLauncher;
  rocketLauncher.id = 2;
  rocketLauncher.x = 0;
  rocketLauncher.y = 0;
  rocketLauncher.width = 60;
  rocketLauncher.height = 20;
  rocketLauncher.fireRate = 3.0f * (float)TARGETFPS;
  rocketLauncher.projectileSpeed = 200.0f;
  rocketLauncher.type = "explosive";
  rocketLauncher.range = 900.0f;
  rocketLauncher.damage = 300;
  rocketLauncher.maxMagSize = 1;
  rocketLauncher.currentMagSize = rocketLauncher.maxMagSize;
  rocketLauncher.maxReserveSize = 4;
  rocketLauncher.currentReserveSize = rocketLauncher.maxReserveSize;
  rocketLauncher.reloadTime = 4.0f;
  rocketLauncher.reloadTimer = 0.0f;
  rocketLauncher.weaponCost = 3000;
  rocketLauncher.ammoCost = 2000;
  rocketLauncher.holding = false;
  return rocketLauncher;
}

void splashDamage(Projectile *projectile, Enemy *enemy,
                         Enemy *enemyArr) {
  float posX = enemy->x + enemy->width / 2.0f;
  float posY = enemy->y + enemy->height / 2.0f;
  float damage = (float)projectile->damage;
  float radius = 200.0f;
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    float dx = posX - enemyArr[i].x;
    float dy = posY - enemyArr[i].y;
    float length = fabs(sqrtf(dx * dx + dy * dy));
    if (length <= radius) {
      float actualDamage = damage * (1.0f - (length / radius));
      enemyLoseHealth(actualDamage, &enemyArr[i]);
    }
  }
  enemyLoseHealth(damage, enemy);
  DrawCircle(posX, posY, radius, YELLOW);
}
