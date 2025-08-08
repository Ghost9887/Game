#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "raylib.h"
#include <stdbool.h>

void enemyMovement(Enemy *enemy, Player *player);
void drawEnemy(Enemy *enemy);
void updateEnemy(Enemy *enemyArr, Player *player);
void initEnemyArr(Enemy *enemyArr);
void destroyEnemy(Enemy *enemy, Player *player, Pickup *pickupArr);
bool checkCollisionWithPlayer(Enemy *enemy, Player *player);
void createEnemies(Enemy *enemArr, int enemyCount, int rnd);
bool checkIfAllEnemiesAreDestroyed(Enemy *enemy);
void enemyLoseHealth(float damage, Enemy *enemy);
void reduceEnemyFakeHealth(Enemy *enemy, float damage);

#endif
