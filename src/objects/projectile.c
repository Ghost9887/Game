#include "projectile.h"
#include "enemy.h"
#include "raylib.h"
#include "player.h"
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

void updateProjectiles(Projectile *projectileArr, Enemy *enemyArr, Player *player) {
  for (int i = 0; i < MAXPROJECTILES; i++) {
    if (projectileArr[i].active) {
      if (checkForCollisionWithEnemy(
              &projectileArr[i], &enemyArr[projectileArr[i].target])) {
        destroyProjectile(&projectileArr[i]);
        //add money for each hit
        addMoney(player, 20);
        // check wether the to do splash damage or ballistic damage
        if (projectileArr[i].explosive) {
          explosiveProjectile(&projectileArr[i],
                              &enemyArr[projectileArr[i].target], enemyArr);
        } else {
          enemyLoseHealth(projectileArr[i].damage,
                          &enemyArr[projectileArr[i].target]);
        }
      }
      moveProjectile(&projectileArr[i], &enemyArr[projectileArr[i].target]);
      drawProjectile(&projectileArr[i]);
      projectileArr[i].lifetime -= GetFrameTime();
      if (projectileArr[i].lifetime <= 0) {
        destroyProjectile(&projectileArr[i]);
      }
    }
  }
}

void destroyProjectile(Projectile *projectile) { projectile->active = false; }

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

void explosiveProjectile(Projectile *projectile, Enemy *enemy,
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
