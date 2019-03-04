#ifndef ASSETS_H_INCLUDED
#define ASSETS_H_INCLUDED

#include "libs.h"

extern SDL_Surface *sudokuGridImg;
extern SDL_Surface *nums[9];
extern SDL_Surface *redNums[9];

bool LoadAssets(void);
void FreeAssets(void);

#endif // ASSETS_H_INCLUDED
