#include "raylib.h"
#include "enemy.h"
#include "ui.h"
#include "roundSystem.h"

extern unsigned int ENEMYCOUNTER;

Round createRoundObject(){
  Round rnd;
  rnd.round = 0;
  rnd.breakTimer = 0.0f;
  rnd.inBreak = false;
  return rnd;
}

int getRound(Round *rnd){
  return rnd->round;
}

bool inBreak(Round *rnd){
  return rnd->inBreak;
}

void reduceBreakTimer(Round *rnd){
  rnd->breakTimer -= GetFrameTime();
}

float getBreakTimer(Round *rnd){
  return rnd->breakTimer;
}

int getAmountOfEnemies(Round *rnd){
  return 6 * getRound(rnd);
}

void changeBreak(bool value, Round *rnd){
  rnd->inBreak = value;
}

void startRound(Round *rnd, Enemy *enemyArr){
  rnd->round = getRound(rnd) + 1; 
  changeBreak(false, rnd);
  ENEMYCOUNTER = getAmountOfEnemies(rnd);
  //spawns the enemies at the start of the round
  createEnemies(enemyArr, getAmountOfEnemies(rnd));
}

void endRound(bool completed, Round *rnd){
  if(completed){
    rnd->inBreak = true;
    rnd->breakTimer = 10.0f;
  }
}

void updateBreak(Round *rnd, Enemy *enemyArr){
  if(!inBreak(rnd)){
  endRound(checkIfAllEnemiesAreDestroyed(enemyArr), rnd);
  }
  else{
    reduceBreakTimer(rnd);
    showBreakUI(getBreakTimer(rnd));
    if(getBreakTimer(rnd) <= 0){
      startRound(rnd, enemyArr);
    }
  }
}


