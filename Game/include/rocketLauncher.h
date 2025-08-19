#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H

#include "common.h"
#include "raylib.h"

Weapon createRocketLauncher();
void splashDamage(Projectile *projectile, Enemy *enemy, Enemy *enemyArr);

#endif
