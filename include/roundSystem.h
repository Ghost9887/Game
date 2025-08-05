#ifndef ROUDNSYSTEM_H
#define ROUNDSYSTEM_H

#include "raylib.h"
#include "common.h"


int getRound(Round *rnd);
int getAmountOfEnemies(Round *rnd);
void startRound(Round *rnd, Enemy* enemyArr);
Round createRoundObject();
void endRound(bool completed, Round *rnd);
bool inBreak(Round *rnd);
void reduceBreakTimer(Round *rnd);
float getBreakTimer(Round *rnd);
void changeBreak(bool value,  Round *rnd);
void updateBreak(Round *rnd, Enemy* enemyArr);


#endif
