#include "weaponbuy.h"
#include "weapon.h"
#include "pistol.h"
#include "assaultRifle.h"
#include "rocketLauncher.h"
#include "smg.h"
#include "shotgun.h"
#include "ui.h"
#include <string.h>


WeaponBuy createWeaponBuy(Weapon *weapon){
  WeaponBuy weaponBuy;
  weaponBuy.x = 0;
  weaponBuy.y = 0;
  weaponBuy.weapon = weapon;
  weaponBuy.weaponCost = weapon->weaponCost;
  weaponBuy.ammoCost = weapon->ammoCost;
  return weaponBuy;
}

void drawWeaponBuy(WeaponBuy *weaponBuy){
  DrawRectangle(weaponBuy->x, weaponBuy->y, weaponBuy->weapon->width, weaponBuy->weapon->height, BLACK);
}

void spawnWeaponBuy(WeaponBuy *weaponBuy, Weapon *weapon){
   
}

//refactor later
void initWeaponBuyArr(WeaponBuy *weaponBuyArr, Weapon *weaponArr){
  for(int i = 0; i < 5; i++){
    weaponBuyArr[i] = createWeaponBuy(&weaponArr[i]);
    if(i < 1){
      weaponBuyArr[i].x = 100;
    }else{
    weaponBuyArr[i].x = i * 250;
    }
    weaponBuyArr[i].y = 650;
  }
}

int checkForCollisionWeaponBuyPlayer(WeaponBuy *weaponBuyArr, Player *player){
  for(int i = 0; i < 5; i++){
  Rectangle weaponBuyRect = {weaponBuyArr[i].x, weaponBuyArr[i].y, weaponBuyArr[i].weapon->width, weaponBuyArr[i].weapon->height};
  Rectangle playerRect = {player->x, player->y, player->width, player->height};
  if(CheckCollisionRecs(weaponBuyRect, playerRect)){
      return i;
    }
  }
  return -1;
}

//HUGE FUNCTION MAYBE REFACTOR?
void buyWeapon(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster){
  int index = checkForCollisionWeaponBuyPlayer(weaponBuyArr, player);
  if (index != -1) {
    Weapon *newWeapon = &weaponArr[index];
    bool alreadyOwned = false;
    for (int i = 0; i < MAXWEAPONS; i++) {
      if (weaponHolster[i] == newWeapon->id) {
        alreadyOwned = true;
        break;
      }
    }
    Color textColour;
    if (alreadyOwned) {
      //determine what colour the text should be if the player has enough money
      textColour = (player->money >= newWeapon->ammoCost) ? GREEN : RED;
      drawAmmoBuyText(textColour, newWeapon, weaponBuyArr[index].x, weaponBuyArr[index].y);
      if (IsKeyPressed(KEY_E) && player->money >= newWeapon->ammoCost) {
        player->money -= newWeapon->ammoCost;
        replenishAmmo(player, newWeapon);
      }
      return;
    } else {
      textColour = (player->money >= newWeapon->weaponCost) ? GREEN : RED;
      drawWeaponBuyText(textColour, newWeapon, weaponBuyArr[index].x, weaponBuyArr[index].y);
    }
    if (IsKeyPressed(KEY_E) && player->money >= newWeapon->weaponCost) {
      int currentWeaponId = player->weapon->id;
      int slotToReplace = -1;
      bool foundEmptySlot = false;
      for (int i = 0; i < MAXWEAPONS; i++) {
        if (weaponHolster[i] == -1) {
          slotToReplace = i;
          foundEmptySlot = true;
          break;
        }
      }
      if (!foundEmptySlot) {
        for (int i = 0; i < MAXWEAPONS; i++) {
          if (weaponHolster[i] == currentWeaponId) {
            slotToReplace = i;
            break;
          }
        }
      }
      if (slotToReplace != -1) {
        weaponHolster[slotToReplace] = newWeapon->id;
        player->money -= newWeapon->weaponCost;
        replaceWeapon(newWeapon, player);
      }
    }
  }
}



void updateWeaponBuy(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster){
  for(int i = 0; i < 5; i++){
    drawWeaponBuy(&weaponBuyArr[i]);
    buyWeapon(weaponBuyArr, player, weaponArr, weaponHolster);
  }
}

