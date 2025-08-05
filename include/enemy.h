#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "raylib.h"
#include <stdbool.h>

void enemyMovement(Enemy *enemy, Player *player);
Enemy createEnemyObject(float posX, float posY);
void drawEnemy(Enemy *enemy);
void updateEnemy(Enemy *enemyArr, Player *player);
void initEnemyArr(Enemy *enemyArr);
int findClosestEnemyToPlayer(Enemy *enemyArr, Player *player, Coins *coins);
float calculateDistance(Enemy *enemy, Player *player);
void destroyEnemy(Enemy *enemy, Coins *coins);
void checkHealth(Enemy *enemy, Coins *coins);
bool checkCollisionWithPlayer(Enemy *enemy, Player *player);
void createEnemies(Enemy *enemArr, int enemyCount);
bool checkIfAllEnemiesAreDestroyed(Enemy *enemy);
void enemyLoseHealth(float damage, Enemy *enemy);

#endif
