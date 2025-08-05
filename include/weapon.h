#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"
#include "raylib.h"

void drawWeapon(Player *player, Weapon *weapon);
void initWeaponArr(Weapon *weaponArr);
void switchWeapons(Player *player, Weapon *weapon);

#endif
