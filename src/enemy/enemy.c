#include "player.h"
#include "enemy.h"
#include "basicEnemy.h"
#include "specialEnemy.h"
#include "ui.h"
#include "pickup.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>


extern unsigned int ENEMYCOUNTER;
extern unsigned int CURRENTSPAWNEDENEMIES;

void drawEnemy(Enemy *enemy){
  DrawRectangle(enemy->x, enemy->y, enemy->width, enemy->height, RED);
}

void initEnemyArr(Enemy *enemyArr) {
  // initialize the projectile array
  for (int i = 0; i < MAXENEMIES; i++) {
    enemyArr[i].active = false;
    enemyArr[i].width = 0.0f;
    enemyArr[i].height = 0;
    enemyArr[i].health = 0;
    enemyArr[i].x = 0;
    enemyArr[i].y = 0;
  }
}

void enemyMovement(Enemy *enemy, Player *player) {
  float deltaTime = GetFrameTime();
  float dx = player->x - enemy->x;
  float dy = player->y - enemy->y;
  float length = sqrtf(dx * dx + dy * dy);
  if (length < 0.1f)
    return;
  float dirX = dx / length;
  float dirY = dy / length;
  enemy->x += dirX * enemy->speed * deltaTime;
  enemy->y += dirY * enemy->speed * deltaTime;
}


void destroyEnemy(Enemy *enemy, Player *player, Pickup *pickupArr) {
  if(enemy->health <= 0){
    enemy->active = false;
    ENEMYCOUNTER--;
    CURRENTSPAWNEDENEMIES--;
    addMoney(player, 60);
    //chance to drop a pickup test refactor later
  //10% chance
  int randomNumber = GetRandomValue(1, 10);
  if(randomNumber == 3){
    int randomPickup = GetRandomValue(1, 2);
    if(randomPickup == 1){
      spawnPickup(pickupArr, enemy->x, enemy->y, "health");
    }
    else if(randomPickup == 2){
      spawnPickup(pickupArr, enemy->x, enemy->y, "ammo");
    }
  }
  }
}

//only checks the closest enemy
bool checkCollisionWithPlayer(Enemy *enemy, Player *player) {
  // create the enemy rectangle from its data
  Rectangle enemyRect = {enemy->x, enemy->y, enemy->width, enemy->height};
  Rectangle playerRect = {player->x, player->y, player->width, player->height};
  return CheckCollisionRecs(enemyRect, playerRect);
}

// spawns the enemies
void createEnemies(Enemy *enemyArr, int enemyCount, int rnd) {
  static bool seeded = false;
  if (!seeded) {
    srand(time(NULL));
    seeded = true;
  }
  // if there are less enemies we dont have to check if there is a available
  // slot
  if (enemyCount <= MAXSPAWNENEMIES) {
    for (int i = 0; i < enemyCount; i++) {
      if(!enemyArr[i].active){
      float randomX = SCREENWIDTH / 2 + rand() % SCREENWIDTH;
      float randomY = SCREENHEIGHT / 2 + rand() % SCREENHEIGHT;
      if(rnd % 5 == 0){
        enemyArr[i] = createSpecialEnemy(randomX, randomY);
        CURRENTSPAWNEDENEMIES++;
      }else{
        enemyArr[i] = createBasicEnemy(randomX, randomY);
        CURRENTSPAWNEDENEMIES++;
      }
      }
    }
  } else {
    for (int i = 0; i < MAXSPAWNENEMIES; i++) {
      if (!enemyArr[i].active) {
        float randomX = rand() % SCREENWIDTH * 2;
        float randomY = rand() % SCREENHEIGHT * 2;
        if(rnd % 5 == 0){
          enemyArr[i] = createSpecialEnemy(randomX, randomY);
          CURRENTSPAWNEDENEMIES++;
        }else{
          enemyArr[i] = createBasicEnemy(randomX, randomY);
          CURRENTSPAWNEDENEMIES++;
        }
      }
    }
  }
}

bool checkIfAllEnemiesAreDestroyed(Enemy *enemy) {
  if (ENEMYCOUNTER == 0) {
    return true;
  }
  return false;
}

void enemyLoseHealth(float damage, Enemy *enemy) { enemy->health -= damage; }

void updateEnemy(Enemy *enemyArr, Player *player, Pickup *pickupArr) {
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    if (!enemyArr[i].active)
      continue;

    enemyMovement(&enemyArr[i], player);
    drawEnemy(&enemyArr[i]);

    //checks if the enemy should die (bad naming)
    destroyEnemy(&enemyArr[i], player, pickupArr);

    // checks collision with player
    if (!isPlayerInvulnerable(player) &&
        checkCollisionWithPlayer(&enemyArr[i], player)) {
      playerLoseHealth(&enemyArr[i], player);
    }

    drawEnemyHealth(&enemyArr[i]);
  }
}



