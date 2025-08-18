#include "projectile.h"
#include "enemy.h"
#include "raylib.h"
#include "player.h"
#include "rocketLauncher.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

Projectile createProjectile(Player *player, Weapon *weapon, float offset) {
  Projectile projectile;
  projectile.x = player->x + player->width / 2;
  projectile.y = player->y + player->height / 2 + 15;
  
  //calculate the directional vector
  float angleDeg = player->weapon->rotation + offset;
  float angleRad = angleDeg * (3.14 / 180.0f);

  projectile.dX = cosf(angleRad);
  projectile.dY = sinf(angleRad);
  projectile.damage = weapon->damage;
  projectile.speed = weapon->projectileSpeed;
  projectile.active = true;
  projectile.size = 5.0f;
  projectile.range = weapon->range;
  projectile.distanceTraveled = 0.0f;
  return projectile;
}

void drawProjectile(Projectile *projectile) {
    Vector2 origin = {projectile->x, projectile->y};
    Vector2 direction = {
        projectile->dX,
        projectile->dY
    };
    float visualLength = 20.0f; 
    Vector2 end = {
        origin.x + direction.x * visualLength,
        origin.y + direction.y * visualLength
    };
    DrawLineEx(origin, end, 2.0f, BLUE);
}


void moveProjectile(Projectile *projectile) {
  float deltaTime = GetFrameTime();
  projectile->previousPos = (Vector2){projectile->x, projectile->y};
  projectile->x += projectile->dX * projectile->speed * deltaTime;
  projectile->y += projectile->dY * projectile->speed * deltaTime;
  float dx = projectile->x - projectile->previousPos.x;
  float dy = projectile->y - projectile->previousPos.y;
  projectile->distanceTraveled += sqrtf(dx * dx + dy * dy);
}

void destroyProjectile(Projectile *projectile) { 

  projectile->speed = 0;
  projectile->active = false; 
}

void initProjectileArray(Projectile *projectileArr) {
  // initialize the projectile array
  for (int i = 0; i < MAXPROJECTILES; i++) {
    projectileArr[i].active = false;
    projectileArr[i].speed = 0.0f;
    projectileArr[i].damage = 0;
    projectileArr[i].range = 0.0f;
    projectileArr[i].distanceTraveled = 0.0f;
    projectileArr[i].x = 0;
    projectileArr[i].y = 0;
  }
}

int checkForCollisionWithEnemy(Projectile *projectile, Enemy *enemyArr) {
    Vector2 currentPos = {projectile->x, projectile->y};
    for (int i = 0; i < MAXSPAWNENEMIES; i++) {
        if (!enemyArr[i].active) continue;
        Rectangle enemyRect = {enemyArr[i].x, enemyArr[i].y, enemyArr[i].width, enemyArr[i].height};
        if (CheckCollisionPointRec(currentPos, enemyRect)) {
            return i;
        }
    }
    return -1;
}

void updateProjectiles(Projectile *projectileArr, Enemy *enemyArr, Player *player) {
  for (int i = 0; i < MAXPROJECTILES; i++) {
    if (!projectileArr[i].active) continue;

    moveProjectile(&projectileArr[i]);

    int indexOfEnemy = checkForCollisionWithEnemy(&projectileArr[i], enemyArr);

    if (indexOfEnemy != -1) {
      destroyProjectile(&projectileArr[i]);
      addMoney(player, 20);

      if (strcmp(player->weapon->type, "explosive") == 0) {
        splashDamage(&projectileArr[i], &enemyArr[indexOfEnemy], enemyArr);
      }
      else {
        enemyLoseHealth(projectileArr[i].damage, &enemyArr[indexOfEnemy]);
      }
      continue; 
    }
    
    //only do these if the projectile hasnt hit anything
    drawProjectile(&projectileArr[i]);

    if (projectileArr[i].distanceTraveled >= projectileArr[i].range) {
      destroyProjectile(&projectileArr[i]);
    }
  }
}

