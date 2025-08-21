#include "map.h"
#include "tile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadMap(int *mapArr){
   FILE *file = fopen("assets/map.mp", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    char buffer[100000]; 
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Failed to read file");
        fclose(file);
        return;
    }
    fclose(file);
    char *comma = strtok(buffer, ",");
    int index = 0;
    while (comma != NULL && index < MAXTILES) {
        mapArr[index] = atoi(comma);
        comma = strtok(NULL, ",");
        index++;
    } 
    printf("Map Loaded Successfully\n");
}

void drawMap(Tile *tileArr, Texture2D *tileTexturesArr, Chunk *chunkArr, Camera2D *camera){

  Rectangle cameraView = {
    camera->target.x - SCREENWIDTH / 2,
    camera->target.y - SCREENHEIGHT / 2,
    SCREENWIDTH,
    SCREENHEIGHT
  };
  //DrawRectangleRec(cameraView, RED);
  for(int i = 0; i < 9; i++){
   if(CheckCollisionRecs(cameraView, chunkArr[i].rec)){
      int index = chunkArr[i].startIndex;
      for(int y = 0; y < 74; y++){
        for(int x = 0; x < 74; x++){
          DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
          index++;
        }
        index += 222 - chunkArr[i].rec.width / 32;
      } 
    }
  }
    
  /*
  //first chunk drawn manually74 * chunkArr[0].rec.x + chunkArr[0].rec.y
  printf("%d\n", chunkArr[0].startIndex);
  int index = chunkArr[0].startIndex;
  for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[0].rec.width / 32;
  }
  printf("Drawn first chunk\n");
  
  //second chunk drawn manually
   index = 74 * chunkArr[1].rec.x + chunkArr[1].rec.y;
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[1].rec.width;
  }

   index = 74 * chunkArr[2].rec.x + chunkArr[2].rec.y;
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[2].rec.width;
  }

  
  int index = 74 * chunkArr[3].rec.x + chunkArr[3].rec.y;
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[3].rec.width;
  }

   index = 74 * chunkArr[4].rec.x + chunkArr[4].rec.y;
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[4].rec.width;
  }

  index = 74 * chunkArr[5].rec.x + chunkArr[5].rec.y;
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[5].rec.width;
  }

  int index = (chunkArr[6].rec.x + chunkArr[6].rec.y);
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[6].rec.width;
  }

  index = (chunkArr[7].rec.x + chunkArr[7].rec.y);
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[7].rec.width;
  }

  index = (chunkArr[8].rec.x + chunkArr[8].rec.y);
   for(int i = 0; i < 74; i++){
    for(int j = 0; j < 74; j++){
      DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
      index++;
    }
    index += 222 - chunkArr[8].rec.width;
  }
*/
}


void initTileArr(Tile *tileArr, int *mapArr) {
    int size = 32;
    int tilesPerRow = 7104 / size;
    int tilesPerColumn = 7104 / size;
    int index = 0;
    for (int y = 0; y < tilesPerColumn; y++) {
        for (int x = 0; x < tilesPerRow; x++) {
            tileArr[index].x = x * size;
            tileArr[index].y = y * size;
            tileArr[index].width = 32;
            tileArr[index].height = 32;
            tileArr[index].active = true;
            tileArr[index].walkable = false;
            tileArr[index].id = mapArr[index];
            index++;
        }
    }
}

void loadTileTextures(Texture2D *tileTexturesArr){
  tileTexturesArr[0] = LoadTexture("assets/tiles/white.png");
  tileTexturesArr[1] = LoadTexture("assets/tiles/tile1.png");
  tileTexturesArr[2] = LoadTexture("assets/tiles/tile2.png");
}
