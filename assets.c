#include "assets.h"

SDL_Surface *sudokuGridImg = NULL; // Sudoku grid image 500*500
SDL_Surface *nums[9]; // Numbers that are images 40*40
SDL_Surface *redNums[9]; // Red answers numbers that are images 40*40

bool LoadAssets(void)
{
    sudokuGridImg = SDL_LoadBMP("assets/sudoku.bmp");
    if (sudokuGridImg == NULL)
        return false;

    // Normal numbers
    nums[0] = SDL_LoadBMP("assets/1.bmp");
    if (nums[0] == NULL)
        return false;
    nums[1] = SDL_LoadBMP("assets/2.bmp");
    if (nums[1] == NULL)
        return false;
    nums[2] = SDL_LoadBMP("assets/3.bmp");
    if (nums[2] == NULL)
        return false;
    nums[3] = SDL_LoadBMP("assets/4.bmp");
    if (nums[3] == NULL)
        return false;
    nums[4] = SDL_LoadBMP("assets/5.bmp");
    if (nums[4] == NULL)
        return false;
    nums[5] = SDL_LoadBMP("assets/6.bmp");
    if (nums[5] == NULL)
        return false;
    nums[6] = SDL_LoadBMP("assets/7.bmp");
    if (nums[6] == NULL)
        return false;
    nums[7] = SDL_LoadBMP("assets/8.bmp");
    if (nums[7] == NULL)
        return false;
    nums[8] = SDL_LoadBMP("assets/9.bmp");
    if (nums[8] == NULL)
        return false;
    
    // Red numbers
    redNums[0] = SDL_LoadBMP("assets/1r.bmp");
    if (redNums[0] == NULL)
        return false;
    redNums[1] = SDL_LoadBMP("assets/2r.bmp");
    if (redNums[1] == NULL)
        return false;
    redNums[2] = SDL_LoadBMP("assets/3r.bmp");
    if (redNums[2] == NULL)
        return false;
    redNums[3] = SDL_LoadBMP("assets/4r.bmp");
    if (redNums[3] == NULL)
        return false;
    redNums[4] = SDL_LoadBMP("assets/5r.bmp");
    if (redNums[4] == NULL)
        return false;
    redNums[5] = SDL_LoadBMP("assets/6r.bmp");
    if (redNums[5] == NULL)
        return false;
    redNums[6] = SDL_LoadBMP("assets/7r.bmp");
    if (redNums[6] == NULL)
        return false;
    redNums[7] = SDL_LoadBMP("assets/8r.bmp");
    if (redNums[7] == NULL)
        return false;
    redNums[8] = SDL_LoadBMP("assets/9r.bmp");
    if (redNums[8] == NULL)
        return false;

    return true;
}

void FreeAssets(void)
{
    SDL_FreeSurface(sudokuGridImg);
    for (int i = 0; i < 9; i++)
        SDL_FreeSurface(nums[i]);
}
