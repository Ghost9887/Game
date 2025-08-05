#include "raylib.h"
#include "coins.h"
#include "player.h"
#include <stdbool.h>

Coins createCoins(){
  Coins coins;
  coins.coinCounter = 0;
  return coins;
}

void addCoins(int amount, Coins *coins){
  coins->coinCounter += amount;
}

void removeCoins(int amount, Coins *coins){
  coins->coinCounter -= amount;
}

bool checkIfHaveEnoughCoins(int amount, Coins *coins){
  if(getCoins(coins) < amount){
    return false;
  }
  return true;
}

int getCoins(Coins *coins){
  return coins->coinCounter;
}
