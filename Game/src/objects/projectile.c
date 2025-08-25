#include "projectile.h"
#include "enemy.h"
#include "raylib.h"
#include "player.h"
#include "rocketLauncher.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

extern unsigned int AMOUNTOFSOLIDBLOCKS;

Projectile createProjectile(Player *player, Weapon *weapon, float offset) {
    Projectile projectile;
    float angleDeg = player->weapon->rotation + offset;
    float angleRad = angleDeg * (3.14159265f / 180.0f);
    float muzzleDistance = player->width * 0.4f;

    projectile.x = player->x + player->width / 2 + cosf(angleRad) * muzzleDistance;
    projectile.y = player->y + player->height / 2 + sinf(angleRad) * muzzleDistance;

    projectile.dX = cosf(angleRad);
    projectile.dY = sinf(angleRad);
    projectile.length = 20.0f;
    projectile.damage = weapon->damage;
    projectile.speed = weapon->projectileSpeed;
    projectile.active = true;
    projectile.size = 5.0f;
    projectile.range = weapon->range;
    projectile.distanceTraveled = 0.0f + projectile.length;

    return projectile;
}


void drawProjectile(Projectile *projectile) {
    Vector2 origin = {projectile->x, projectile->y};
    Vector2 direction = {
        projectile->dX,
        projectile->dY
    };
    Vector2 end = {
        origin.x + direction.x * projectile->length,
        origin.y + direction.y * projectile->length
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

int checkForCollisionWithEnemy(Projectile *projectile, Enemy *enemyArr, Tile *solidTileArr) {
    Vector2 currentPos = {projectile->x, projectile->y};
    
      //tiles
    for (int i = 0; i < AMOUNTOFSOLIDBLOCKS; i++) {
        Rectangle tileRect = {
            solidTileArr[i].x,
            solidTileArr[i].y,
            solidTileArr[i].width,
            solidTileArr[i].height
        };
        if (CheckCollisionPointRec(currentPos, tileRect)) {
            return -2;  
        }
    }

    //enemies
    for (int i = 0; i < MAXSPAWNENEMIES; i++) {
        if (!enemyArr[i].active) continue;
        Rectangle enemyRect = {enemyArr[i].x, enemyArr[i].y, enemyArr[i].width, enemyArr[i].height};
        if (CheckCollisionPointRec(currentPos, enemyRect)) {
            return i;
        }
    }
    return -1;
}


void updateProjectiles(Projectile *projectileArr, Enemy *enemyArr, Player *player, Tile *solidTileArr) {
  for (int i = 0; i < MAXPROJECTILES; i++) {
    if (!projectileArr[i].active) continue;

    moveProjectile(&projectileArr[i]);

    int indexOfEnemy = checkForCollisionWithEnemy(&projectileArr[i], enemyArr, solidTileArr);

    if (indexOfEnemy > -1) {
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
  
    //hit wall
    if(indexOfEnemy == -2){
      destroyProjectile(&projectileArr[i]);
    }
    
    //only do these if the projectile hasnt hit anything
    drawProjectile(&projectileArr[i]);

    if (projectileArr[i].distanceTraveled >= projectileArr[i].range) {
      destroyProjectile(&projectileArr[i]);
    }
  }
}

