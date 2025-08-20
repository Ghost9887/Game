#include "camera.h"

void initCamera(Camera2D *camera, Player *player){
  camera->zoom = 1.0f;
  camera->rotation = 0.0f;
  camera->offset = (Vector2){ SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f }; // center of screen
  camera->target = (Vector2){ player->x + player->width / 2, player->y + player->height / 2 };

}

void updateCamera(Camera2D *camera, Player *player){ camera->target = (Vector2){ player->x + player->width / 2, player->y + player->height / 2 };
}
