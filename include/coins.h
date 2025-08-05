#ifndef COINS_H
#define COINS_H

#include "raylib.h"
#include "common.h"
#include <stdbool.h>

void addCoins(int amount, Coins *coins);

void removeCoins(int amount, Coins *coins);

bool checkIfHaveEnoughCoins(int amount, Coins *coins);

int getCoins(Coins *coins);

Coins createCoins();

#endif
