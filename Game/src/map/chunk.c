#include "chunk.h"

Chunk createChunk(int id, Rectangle rec, int index){
  Chunk chunk;
  chunk.id = id;
  chunk.rec = rec;
  chunk.startIndex = index; 
  return chunk;
}

void initChunkArr(Chunk *chunkArr){
  //9 chunks
  //definetily a way to calculate the start index and the x and y of the rect
  //but i just couldnt figure it out so it looks horrible but works for now
  Rectangle rec = {0, 0, 2368, 2368};
  chunkArr[0] = createChunk(1, rec, 0);

  Rectangle rec1 = {0, 2368, 2368, 2368};
  chunkArr[1] = createChunk(2, rec1, 16428);

  Rectangle rec2 = {0, 4736, 2368, 2368};
  chunkArr[2] = createChunk(3, rec2, 32856);

  Rectangle rec3 = {2368, 0, 2368, 2368};
  chunkArr[3] = createChunk(4, rec3, 74);

  Rectangle rec4 = {2368, 2368, 2368, 2368};
  chunkArr[4] = createChunk(5, rec4, 16502);

  Rectangle rec5 = {2368, 4736, 2368, 2368};
  chunkArr[5] = createChunk(6, rec5, 32930);

  Rectangle rec6 = {4736, 0, 2368, 2368};
  chunkArr[6] = createChunk(7, rec6, 148);

  Rectangle rec7 = {4736, 2368, 2368, 2368};
  chunkArr[7] = createChunk(8, rec7, 16576);

  Rectangle rec8 = {4736, 4736, 2368, 2368};
  chunkArr[8] = createChunk(9, rec8, 33004);
  
}
