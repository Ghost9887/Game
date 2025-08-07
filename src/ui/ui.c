#include "raylib.h"
#include "ui.h"
#include "player.h"

void drawUI(int health, int enemyCounter, float invTimer, int lvl,
            int money, int spawnedEnemies, int fps,
            int magAmmo, int reserveAmmo, float reloadTimer){
  DrawText(TextFormat("Health: %d", health), 25, 25, 40, BLACK);
  DrawText(TextFormat("Vulnerable: %f", invTimer), 25, 135, 40, BLACK);
  DrawText(TextFormat("Round: %d", lvl), 25, 180, 40, BLACK);
  DrawText(TextFormat("Enemy count: %d", enemyCounter), 25, 80, 40, BLACK);
  DrawText(TextFormat("Money: %d", money), 25, 235, 40, BLACK);
  DrawText(TextFormat("Spawned enemies: %d", spawnedEnemies), 25, 290, 40, BLACK);
  DrawText(TextFormat("Reload: %f", reloadTimer), 25, 340, 40, BLACK);
  DrawText(TextFormat("FPS: %d", fps), 1100, 25, 20, BLUE);
  DrawText(TextFormat("%d", magAmmo), 25, 700, 30, RED);
  DrawText(TextFormat("/ %d", reserveAmmo), 70, 700, 20, BLACK);
}

void showBreakUI(int time){
  DrawText(TextFormat("Time until next round: %d", time), SCREENWIDTH / 2, 40, 20, RED);
}

void drawEnemyHealth(Enemy *enemy){
  DrawText(TextFormat("%d", (int) enemy->health), enemy->x + enemy->width / 2 - 10, 
           enemy->y + enemy->height / 2 - 60, 20, RED);
}


