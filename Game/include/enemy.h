#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "raylib.h"
#include <stdbool.h>

void enemyMovement(Enemy *enemy, Player *player);
void drawEnemy(Enemy *enemy, Texture2D *enemyTexturesArr);
void updateEnemy(Enemy *enemyArr, Player *player, Pickup *pickupArr, Texture2D *enemyTexturesArr);
void initEnemyArr(Enemy *enemyArr);
void destroyEnemy(Enemy *enemy, Player *player, Pickup *pickupArr);
bool checkCollisionWithPlayer(Enemy *enemy, Player *player);
void createEnemies(Enemy *enemArr, int totalToSpawn, int rnd);
bool checkIfAllEnemiesAreDestroyed(Enemy *enemy);
void enemyLoseHealth(float damage, Enemy *enemy);
void resetBigEnemyCounter();
int getActiveEnemyCount(Enemy *enemyArr);
void loadEnemyTextures(Texture2D *enemyTexturesArr);

#endif
