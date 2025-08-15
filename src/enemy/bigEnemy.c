#include "bigEnemy.h"


Enemy createBigEnemy(float posX, float posY){
  Enemy enemy;
  enemy.id = 2;
  enemy.x = posX;
  enemy.y = posY;
  enemy.width = 128;
  enemy.height = 128;
  enemy.health = 600;
  enemy.damage = 70;
  enemy.speed = 50.0f;
  enemy.money = 200;
  enemy.active = true;
  //animations
  enemy.currentFrame = 0;
  enemy.frameTime = 0.0f;
  enemy.frameSpeed = 0.1f; // seconds per frame
  // used for selecting the coordinates on the sprite sheet
  enemy.frameRec = (Rectangle){ 0.0f, 0.0f, 128.0f, 128.0f};
  return enemy;
}

