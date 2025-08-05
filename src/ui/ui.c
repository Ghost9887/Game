#include "raylib.h"
#include "ui.h"
#include "player.h"

extern const unsigned int SCREENWIDTH;
extern const unsigned int SCRRENHEIGHT;

void drawUI(int health, int enemyCounter, float invTimer, int lvl, int coins, int spawnedEnemies){
  DrawText(TextFormat("Health: %d", health), 25, 25, 40, BLACK);
  DrawText(TextFormat("Vulnerable: %f", invTimer), 25, 135, 40, BLACK);
  DrawText(TextFormat("Round: %d", lvl), 25, 180, 40, BLACK);
  DrawText(TextFormat("Enemy count: %d", enemyCounter), 25, 80, 40, BLACK);
  DrawText(TextFormat("Coins: %d", coins), 25, 235, 40, BLACK);
  DrawText(TextFormat("Spawned enemies: %d", spawnedEnemies), 25, 290, 40, BLACK);
}

void showBreakUI(int time){
  DrawText(TextFormat("Time until next round: %d", time), SCREENWIDTH / 2, 40, 20, RED);
}


