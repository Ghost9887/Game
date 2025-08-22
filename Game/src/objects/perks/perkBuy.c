#include "perkBuy.h"
#include "healthPerk.h"
#include "speedPerk.h"
#include "ui.h"
#include <string.h>
#include <stdio.h>

extern unsigned int AMOUNTOFPERKMACHINES;

PerkBuy createPerkBuy(){
  PerkBuy perkBuy;
  perkBuy.x = 0;
  perkBuy.y = 0;
  perkBuy.width = 32;
  perkBuy.height = 32;
  perkBuy.perk = NULL;
  perkBuy.cost = 0;
  return perkBuy;
}


void initPerkBuyArr(PerkBuy *perkBuyArr){
  for(int i = 0; i < MAXPERKMACHINES; i++){
    perkBuyArr[i] = createPerkBuy();
  }
}

void loadPerkBuyTextures(Texture2D *perkTextureArr){
  perkTextureArr[0] = LoadTexture("assets/perks/health.png");
  perkTextureArr[1] = LoadTexture("assets/perks/speed.png");
}

void drawPerkBuy(PerkBuy *perkBuy, Texture2D *perkTexture){
  Texture2D texture = *perkTexture;
  Rectangle rect = {0, 0, 32, 32};

  Vector2 drawPos = {
    perkBuy->x + (perkBuy->width / 2.0f) - (perkBuy->width / 2.0f),
    perkBuy->y + (perkBuy->height / 2.0f) - (perkBuy->height / 2.0f)
  };
  DrawTextureRec(texture, rect, drawPos, WHITE);
}



int checkCollisionWithPerkPlayer(PerkBuy *perkBuyArr, Player *player){
   for(int i = 0; i < AMOUNTOFPERKMACHINES; i++){
    if(!perkBuyArr[i].perk->consumed){
      Rectangle perkMachineRect = {perkBuyArr[i].x, perkBuyArr[i].y, 40, 80};
      Rectangle playerRect = {player->x, player->y, player->width, player->height};
      if(CheckCollisionRecs(perkMachineRect, playerRect)){
        return i;
      }
    }
  }
    return -1;
}

void spawnPerkBuy(PerkBuy *perkBuyArr, Perk *perk, float x, float y){
  perkBuyArr[AMOUNTOFPERKMACHINES].x = x;
  perkBuyArr[AMOUNTOFPERKMACHINES].y = y;
  perkBuyArr[AMOUNTOFPERKMACHINES].perk = perk;
  perkBuyArr[AMOUNTOFPERKMACHINES].cost = perk->cost;
  AMOUNTOFPERKMACHINES++;
}

void consumePerk(PerkBuy *perkBuyArr, Player *player){
  int indexOfPerk = checkCollisionWithPerkPlayer(perkBuyArr, player);
  if(indexOfPerk != -1){
    Color colour = (perkBuyArr[indexOfPerk].cost <= player->money) ? GREEN : RED;
    drawPerkText(colour, &perkBuyArr[indexOfPerk]);
    if(IsKeyPressed(KEY_E)&& player->money >= perkBuyArr[indexOfPerk].perk->cost && !perkBuyArr[indexOfPerk].perk->consumed){
      if(strcmp(perkBuyArr[indexOfPerk].perk->type, "health") == 0){
        player->maxHealth = perkBuyArr[indexOfPerk].perk->data;
        player->health = player->maxHealth;
        player->money -= perkBuyArr[indexOfPerk].perk->cost;
      }
      else if(strcmp(perkBuyArr[indexOfPerk].perk->type, "speed") == 0){
        player->maxSpeed = perkBuyArr[indexOfPerk].perk->data;
        player->speed = player->maxSpeed;
        player->money -= perkBuyArr[indexOfPerk].perk->cost;
      }
      perkBuyArr[indexOfPerk].perk->consumed = true;
    }
  }
}

//when the player dies the perks get reset
void unconsumeAllPerks(Perk *perkArr){
  for(int i = 0; i < 2; i++){
    perkArr[i].consumed = false; 
  }
}

void updatePerkBuy(PerkBuy *perkBuyArr, Player *player, Texture2D *perkTextureArr){
  for(int i = 0; i < AMOUNTOFPERKMACHINES; i++){

    drawPerkBuy(&perkBuyArr[i], &perkTextureArr[i]);
  }
  consumePerk(perkBuyArr, player);
}
