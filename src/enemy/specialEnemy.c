#include "specialEnemy.h"

Enemy createSpecialEnemy(float posX, float posY){
  Enemy enemy;
  enemy.x = posX;
  enemy.y = posY;
  enemy.width = 15;
  enemy.height = 30;
  enemy.health = 50;
  enemy.fakeHealth = 50;
  enemy.speed = 100.0f;
  enemy.damage = 15;
  enemy.active = true;
  return enemy;
} 
