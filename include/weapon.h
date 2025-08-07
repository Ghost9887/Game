#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"
#include "raylib.h"

void drawWeapon(Player *player);
void initWeaponArr(Weapon *weaponArr);
void switchWeapons(Player *player, Weapon *weapon);
void updateWeapon(Weapon *weaponArr, Player *player);
void checkReload(Weapon *weapon, Player *player);
int getMagAmmo(Weapon *weapon);
int getReserveAmmo(Weapon *weapon);
void reduceAmmo(Weapon *weapon);

#endif
