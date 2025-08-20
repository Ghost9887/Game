#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "common.h"

void initCamera(Camera2D *camera, Player *player);
void updateCamera(Camera2D *camera, Player *player);

#endif
