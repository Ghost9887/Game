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
  projectile.y = player->y + player->height / 2;
  
  //calculate the directional vector
  float angleDeg = player->weapon->rotation + offset;
  float angleRad = angleDeg * (3.14 / 180.0f);

  projectile.dX = cosf(angleRad);
  projectile.dY = sinf(angleRad);
  projectile.damage = weapon->damage;
  projectile.speed = weapon->projectileSpeed;
  projectile.active = true;
  projectile.lifetime = 10.0f;
  projectile.size = 5.0f;
  return projectile;
}

void drawProjectile(Projectile *projectile) {
  DrawCircle(projectile->x, projectile->y, projectile->size, BLACK);
}

void moveProjectile(Projectile *projectile) {
  
  float deltaTime = GetFrameTime();
  
  projectile->previousPos = (Vector2){projectile->x, projectile->y};

  projectile->x += projectile->dX * projectile->speed * deltaTime;
  projectile->y += projectile->dY * projectile->speed * deltaTime;
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

//helper function
bool CheckLineRectCollision(Vector2 start, Vector2 end, Rectangle rect) {
    Vector2 topLeft = {rect.x, rect.y};
    Vector2 topRight = {rect.x + rect.width, rect.y};
    Vector2 bottomLeft = {rect.x, rect.y + rect.height};
    Vector2 bottomRight = {rect.x + rect.width, rect.y + rect.height};

    return CheckCollisionLines(start, end, topLeft, topRight, NULL) ||
           CheckCollisionLines(start, end, topRight, bottomRight, NULL) ||
           CheckCollisionLines(start, end, bottomRight, bottomLeft, NULL) ||
           CheckCollisionLines(start, end, bottomLeft, topLeft, NULL);
}


int checkForCollisionWithEnemy(Projectile *projectile, Enemy *enemyArr) {
    Vector2 previousPos = projectile->previousPos;
    Vector2 currentPos = {projectile->x, projectile->y};

    for (int i = 0; i < MAXSPAWNENEMIES; i++) {
        if (!enemyArr[i].active) continue;

        Rectangle enemyRect = {enemyArr[i].x, enemyArr[i].y, enemyArr[i].width, enemyArr[i].height};

        if (CheckLineRectCollision(previousPos, currentPos, enemyRect)) {
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

    projectileArr[i].lifetime -= GetFrameTime();
    if (projectileArr[i].lifetime <= 0) {
      destroyProjectile(&projectileArr[i]);
    }
  }
}

