#include "specialEnemy.h"

Enemy createSpecialEnemy(float posX, float posY){
  Enemy enemy;
  enemy.id = 1;
  enemy.x = posX;
  enemy.y = posY;
  enemy.width = 34;
  enemy.height = 34;
  enemy.health = 50;
  enemy.speed = 100.0f;
  enemy.damage = 15;
  enemy.money = 50;
  enemy.active = true;
  //animations
  enemy.currentFrame = 0;
  enemy.frameTime = 0.0f;
  enemy.frameSpeed = 0.1f; // seconds per frame
  // used for selecting the coordinates on the sprite sheet
  enemy.frameRec = (Rectangle){ 0.0f, 0.0f, 34.0f, 34.0f};
  return enemy;
} 
