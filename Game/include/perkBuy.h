#ifndef PERKBUY_H
#define PERKBUY_H

#include "raylib.h"
#include "common.h"
  
  PerkBuy createPerkBuy();
  void initPerkBuyArr(PerkBuy *perkBuyArr);
  void loadPerkBuyTextures(Texture2D *perkTextureArr);
  void drawPerkBuy(PerkBuy *perkBuy, Texture2D *perkTexture);
  void consumePerk(PerkBuy *perkBuyArr, Player *player);
  void spawnPerkBuy(PerkBuy *perkBuyArr, Perk *perk, float x, float y);
  void updatePerkBuy(PerkBuy *perkBuyArr, Player *player, Texture2D *perkTextureArr);
  int  checkCollisionWithPerkPlayer(PerkBuy *perkBuyArr, Player *player);
  void unconsumeAllPerks(Perk *perkArr);

#endif
