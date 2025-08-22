#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "common.h"

void drawUI(int health, int enemyCounter, float invTimer, int lvl,
            int money, int spawnedEnemies, int fps,
            int magAmmo, int reserveAmmo, float reloadTimer);
void showBreakUI(int time);
void drawEnemyHealth(Enemy *enemy);
void drawWeaponBuyText(Color colour, WeaponBuy *weaponBuy);
void drawAmmoBuyText(Color colour, WeaponBuy *weaponBuy);
void drawPerkText(Color colour, PerkBuy *perkBuy);

#endif
