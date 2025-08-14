#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "common.h"

void drawUI(int health, int enemyCounter, float invTimer, int lvl,
            int money, int spawnedEnemies, int fps,
            int magAmmo, int reserveAmmo, float reloadTimer);
void showBreakUI(int time);
void drawEnemyHealth(Enemy *enemy);
void drawWeaponBuyText(Color colour, Weapon *weapon, float x, float y);
void drawAmmoBuyText(Color colour, Weapon *weapon, float x, float y);

#endif
