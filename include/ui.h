#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "common.h"

void drawUI(int health, int enemyCounter, float invTimer, int lvl, int coins, int spawnedEnemies);
void showBreakUI(int time);

#endif
