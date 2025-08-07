#include "projectile.h"
#include "enemy.h"
#include "raylib.h"
#include "player.h"
#include "rocketLauncher.h"
#include <math.h>
#include <stdio.h>

Projectile createProjectile(int indexOfEnemy, Player *player, Weapon *weapon) {
  Projectile projectile;
  projectile.x = player->x;
  projectile.y = player->y;
  projectile.damage = weapon->damage;
  projectile.target = indexOfEnemy;
  projectile.speed = weapon->projectileSpeed;
  projectile.active = true;
  projectile.lifetime = 10.0f;
  projectile.size = 5.0f;
  projectile.explosive = false;
  return projectile;
}

void drawProjectile(Projectile *projectile) {
  DrawCircle(projectile->x, projectile->y, projectile->size, BLACK);
}

void moveProjectile(Projectile *projectile, Enemy *enemy) {
  float deltaTime = GetFrameTime();
  float dx = (enemy->x + enemy->width / 2) - projectile->x;
  float dy = (enemy->y + enemy->height / 2) - projectile->y;
  float length = sqrt(dx * dx + dy * dy);
  float dirX = dx / length;
  float dirY = dy / length;
  projectile->x += dirX * projectile->speed * deltaTime;
  projectile->y += dirY * projectile->speed * deltaTime;
}

void destroyProjectile(Projectile *projectile) { 
  projectile->speed = 0;
  projectile->active = false; 
}

void initProjectileArray(Projectile *projectileArr) {
  // initialize the projectile array
  for (int i = 0; i < MAXPROJECTILES; i++) {
    projectileArr[i].active = false;
    projectileArr[i].lifetime = 0.0f;
    projectileArr[i].speed = 0.0f;
    projectileArr[i].damage = 0;
    projectileArr[i].x = 0;
    projectileArr[i].y = 0;
  }
}

bool checkForCollisionWithEnemy(Projectile *projectile, Enemy *enemy) {
  // create the enemy rectangle from its data
  Rectangle enemyRect = {enemy->x, enemy->y, enemy->width, enemy->height};
  return CheckCollisionCircleRec((Vector2){projectile->x, projectile->y},
                                 projectile->size, enemyRect);
}

void updateProjectiles(Projectile *projectileArr, Enemy *enemyArr, Player *player) {
  for (int i = 0; i < MAXPROJECTILES; i++) {
    if (!projectileArr[i].active) continue;

    moveProjectile(&projectileArr[i], &enemyArr[projectileArr[i].target]);

    if (checkForCollisionWithEnemy(&projectileArr[i], &enemyArr[projectileArr[i].target])) {
      destroyProjectile(&projectileArr[i]);
      addMoney(player, 20);

      if (projectileArr[i].explosive) {
        splashDamage(&projectileArr[i], &enemyArr[projectileArr[i].target], enemyArr);
      } else {
        enemyLoseHealth(projectileArr[i].damage, &enemyArr[projectileArr[i].target]);
      }

      continue; 
    }
    
    //only do these if the projectile hasnt hit anything
    drawProjectile(&projectileArr[i]);

    projectileArr[i].lifetime -= GetFrameTime();
    if (projectileArr[i].lifetime <= 0) {
      destroyProjectile(&projectileArr[i]);
    }
  }
}

