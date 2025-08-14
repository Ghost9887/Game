#ifndef WEAPONBUY_H
#define WEAPONBUY_H

#include "raylib.h"
#include "common.h"
#include <stdbool.h>

WeaponBuy createWeaponBuy(Weapon *weapon);
void drawWeaponBuy(WeaponBuy *weaponBuy);
void spawnWeaponBuy(WeaponBuy *weaponBuy, Weapon *weapon);
void initWeaponBuyArr(WeaponBuy *weaponBuyArr, Weapon *weaponArr);
void updateWeaponBuy(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster);
void buyWeapon(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster);
int checkForCollisionWeaponBuyPlayer(WeaponBuy *weaponBuyArr, Player *player);
bool isWeaponOwned(int weaponId, int *weaponHolster);

#endif
