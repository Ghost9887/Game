#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "common.h"

void drawBottomBar(Texture2D *tileTextureArr);
void updateUI(Texture2D *tileTextureArr, User *user);
void checkInput(Texture2D *tileTextureArr, User *user);

#endif
