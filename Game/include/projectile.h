#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "common.h"

Projectile createProjectile(Player *player, Weapon *weapon, float offset);
void drawProjectile(Projectile *projectile);
void moveProjectile(Projectile *projectile);
void updateProjectiles(Projectile *projectileArr, Enemy *enemyArr, Player *player);
void destroyProjectile(Projectile *projectile);
void initProjectileArray(Projectile *projectileArr);
int checkForCollisionWithEnemy(Projectile *projectile, Enemy *enemyArr);

#endif
