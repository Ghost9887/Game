#ifndef CHUNK_H
#define CHUNK_H

#include "raylib.h"
#include "common.h"

  Chunk createChunk(int id, Rectangle rec, int startIndex);
  void initChunkArr(Chunk *chunkArr); 

#endif
