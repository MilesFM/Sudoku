#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include "libs.h"
#include "assets.h"

enum modes
{
    NORMAL_MODE,
    CREATION_MODE,
    AI_MODE
};

extern enum modes mode;
extern int diffculty;
extern int squaresLeft;
extern bool quit;

extern int sudokuAnswers[9][9];
extern int sudokuGrid[9][9];
extern bool wrongGrid[9][9];

extern SDL_Point windowSize;
extern SDL_Window *window;
extern SDL_Surface *screenSurface;

void Events(void);
void Draw(void);
void CleanUp(void);

#endif // SUDOKU_H_INCLUDED
