#include "perk.h"
#include "healthPerk.h"
#include "speedPerk.h"
#include "ui.h"
#include <string.h>


void drawPerk(Perk *perk){
  Color colour;
  if(strcmp(perk->type, "health") == 0){
    colour = GREEN;
  }
  else if(strcmp(perk->type, "speed") == 0){
    colour = YELLOW;
  }
  DrawRectangle(perk->x, perk->y, 40, 80, colour);
}

void initPerkArr(Perk *perkArr){
  perkArr[0] = createHealthPerk();
  perkArr[1] = createSpeedPerk();
}

int checkCollisionWithPerkPlayer(Perk *perkArr, Player *player){
   for(int i = 0; i < 2; i++){
    if(!perkArr[i].consumed){
      Rectangle perkMachineRect = {perkArr[i].x, perkArr[i].y, 40, 80};
      Rectangle playerRect = {player->x, player->y, player->width, player->height};
      if(CheckCollisionRecs(perkMachineRect, playerRect)){
        return i;
      }
    }
  }
    return -1;
}

void consumePerk(Perk *perkArr, Player *player){
  int indexOfPerk = checkCollisionWithPerkPlayer(perkArr, player);
  if(indexOfPerk != -1){
    Color colour = (perkArr[indexOfPerk].cost <= player->money) ? GREEN : RED;
    drawPerkText(colour, &perkArr[indexOfPerk]);
    if(IsKeyPressed(KEY_E)&& player->money >= perkArr[indexOfPerk].cost && !perkArr[indexOfPerk].consumed){
      if(strcmp(perkArr[indexOfPerk].type, "health") == 0){
        player->maxHealth = perkArr[indexOfPerk].data;
        player->health = player->maxHealth;
        player->money -= perkArr[indexOfPerk].cost;
      }
      else if(strcmp(perkArr[indexOfPerk].type, "speed") == 0){
        player->maxSpeed = perkArr[indexOfPerk].data;
        player->speed = player->maxSpeed;
        player->money -= perkArr[indexOfPerk].cost;
      }
      perkArr[indexOfPerk].consumed = true;
    }
  }
}

//when the player dies the perks get reset
void unconsumeAllPerks(Perk *perkArr){
  for(int i = 0; i < 2; i++){
    perkArr[i].consumed = false; 
  }
}

void updatePerk(Perk *perkArr, Player *player){
  for(int i = 0; i < 2; i++){
    drawPerk(&perkArr[i]);
  }
  consumePerk(perkArr, player);
}
