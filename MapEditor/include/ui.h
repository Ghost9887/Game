#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "common.h"
#include <stdbool.h>

void drawBottomBar(Texture2D *tileTextureArr);
void updateUI(Texture2D *tileTextureArr, User *user);
bool checkCollisionWithSaveButton();

#endif
