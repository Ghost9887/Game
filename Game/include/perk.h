#ifndef PERK_H
#define PERK_H

#include "raylib.h"
#include "common.h"

  void drawPerks(Perk *perk);
  void consumePerk(Perk *perkArr, Player *player);
  void initPerkArr(Perk *perkArr);
  void updatePerk(Perk *perkArr, Player *player);
  int checkCollisionWithPerkPlayer(Perk *perkArr, Player *player);
  void unconsumeAllPerks(Perk *perkArr);

#endif
