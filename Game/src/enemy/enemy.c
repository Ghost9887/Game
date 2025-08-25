#include "player.h"
#include "enemy.h"
#include "basicEnemy.h"
#include "specialEnemy.h"
#include "bigEnemy.h"
#include "ui.h"
#include "pickup.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

extern unsigned int ENEMYCOUNTER;
extern unsigned int CURRENTSPAWNEDENEMIES;
extern unsigned int BIGENEMYCOUNTER;
extern unsigned int AMOUNTOFSOLIDBLOCKS;

void drawEnemy(Enemy *enemy, Texture2D *enemyTexturesArr){
  Vector2 pos = {
    enemy->x,
    enemy->y
  };
  DrawTextureRec(enemyTexturesArr[enemy->id], enemy->frameRec, pos, WHITE);
}

void loadEnemyTextures(Texture2D *enemyTexturesArr){
  enemyTexturesArr[0] = LoadTexture("assets/enemies/basic_enemy/basic_enemy.png");
  enemyTexturesArr[1] = LoadTexture("assets/enemies/special_enemy/special_enemy.png");
  enemyTexturesArr[2] = LoadTexture("assets/enemies/big_enemy/big_enemy.png");
}

void updateEnemyAnimation(Enemy *enemy) {
    enemy->frameTime += GetFrameTime();
    if (enemy->frameTime >= enemy->frameSpeed) {
        enemy->frameTime = 0.0f;
        enemy->currentFrame++;
        if (enemy->currentFrame > 2) enemy->currentFrame = 0;
        enemy->frameRec.y = (float)enemy->currentFrame * enemy->frameRec.width;
    }
}

void initEnemyArr(Enemy *enemyArr) {
  // initialize the projectile array
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    enemyArr[i].active = false;
    enemyArr[i].width = 0.0f;
    enemyArr[i].height = 0;
    enemyArr[i].health = 0;
    enemyArr[i].x = 0;
    enemyArr[i].y = 0;
  }
}

void enemyMovement(Enemy *enemy, Player *player, Tile *solidTileArr) {
    float deltaTime = GetFrameTime();
    float dx = player->x - enemy->x;
    float dy = player->y - enemy->y;
    float length = sqrtf(dx * dx + dy * dy);

    if (length < 0.1f)
        return;

    float dirX = dx / length;
    float dirY = dy / length;

    float proposedX = enemy->x + dirX * enemy->speed * deltaTime;
    float proposedY = enemy->y + dirY * enemy->speed * deltaTime;
    Rectangle futureX = { proposedX, enemy->y, enemy->width, enemy->height };
    bool xBlocked = false;
    for (int i = 0; i < AMOUNTOFSOLIDBLOCKS; i++) {
        Rectangle tile = {
            solidTileArr[i].x,
            solidTileArr[i].y,
            solidTileArr[i].width,
            solidTileArr[i].height
        };
        if (CheckCollisionRecs(futureX, tile)) {
            xBlocked = true;
            break;
        }
    }
    if (!xBlocked) enemy->x = proposedX;
    Rectangle futureY = { enemy->x, proposedY, enemy->width, enemy->height };
    bool yBlocked = false;
    for (int i = 0; i < AMOUNTOFSOLIDBLOCKS; i++) {
        Rectangle tile = {
            solidTileArr[i].x,
            solidTileArr[i].y,
            solidTileArr[i].width,
            solidTileArr[i].height
        };
        if (CheckCollisionRecs(futureY, tile)) {
            yBlocked = true;
            break;
        }
    }
    if (!yBlocked) enemy->y = proposedY;
}



void destroyEnemy(Enemy *enemy, Player *player, Pickup *pickupArr) {
  if(enemy->health <= 0){
    enemy->active = false;
    ENEMYCOUNTER--;
    CURRENTSPAWNEDENEMIES--;
    addMoney(player, enemy->money);
    //chance to drop a pickup test refactor later
  //10% chance
  int randomNumber = GetRandomValue(1, 10);
  if(randomNumber == 3){
    int randomPickup = GetRandomValue(1, 2);
    if(randomPickup == 1){
      spawnPickup(pickupArr, enemy->x, enemy->y, "health", player);
    }
    else if(randomPickup == 2){
      spawnPickup(pickupArr, enemy->x, enemy->y, "ammo", player);
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

//checks how many enemies are spawned
int getActiveEnemyCount(Enemy *enemyArr) {
  int count = 0;
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    if (enemyArr[i].active) {
      count++;
    }
  }
  return count;
}

//spawns enemies
void createEnemies(Enemy *enemyArr, int totalToSpawn, int rnd) {
  static bool seeded = false;
  if (!seeded) {
    srand(time(NULL));
    seeded = true;
  }

  int activeCount = getActiveEnemyCount(enemyArr);
  int spawnable = MAXSPAWNENEMIES - activeCount;
  int spawnCount = (totalToSpawn < spawnable) ? totalToSpawn : spawnable;

  for (int i = 0; i < MAXSPAWNENEMIES && spawnCount > 0; i++) {
    if (!enemyArr[i].active) {
      float randomX = SCREENWIDTH / 2 + rand() % SCREENWIDTH;
      float randomY = SCREENHEIGHT / 2 + rand() % SCREENHEIGHT;

      if (rnd % 5 == 0) {
        enemyArr[i] = createSpecialEnemy(randomX, randomY);
      } 
      //only spawn one for this round
      else if(rnd > 8 && rnd < 10 && BIGENEMYCOUNTER < 1){
        enemyArr[i] = createBigEnemy(randomX, randomY);
        BIGENEMYCOUNTER++;
      }
      //spawn multiple big enemies from this round every round depending on round round level ->
      //the amount of big enemies spawn
      else if (rnd > 15 && BIGENEMYCOUNTER <= (int)(rnd / 12)) {
        enemyArr[i] = createBigEnemy(randomX, randomY);
        BIGENEMYCOUNTER++;
      } else {
        enemyArr[i] = createBasicEnemy(randomX, randomY);
      }
      CURRENTSPAWNEDENEMIES++;
      spawnCount--;
    }
  }
}


void resetBigEnemyCounter(){
  BIGENEMYCOUNTER = 0;
}

bool checkIfAllEnemiesAreDestroyed(Enemy *enemy) {
  if (ENEMYCOUNTER == 0) {
    return true;
  }
  return false;
}

void enemyLoseHealth(float damage, Enemy *enemy) { enemy->health -= damage; }

void updateEnemy(Enemy *enemyArr, Player *player, Pickup *pickupArr, Texture2D *enemyTexturesArr, Tile *solidTileArr) {
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    if (!enemyArr[i].active)
      continue;

    enemyMovement(&enemyArr[i], player, solidTileArr);
    updateEnemyAnimation(&enemyArr[i]);
    drawEnemy(&enemyArr[i], enemyTexturesArr);

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



