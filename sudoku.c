#include "sudoku.h"

static bool checkAnswersGrid = false;

enum modes mode = NORMAL_MODE;
int diffculty = 50;
int squaresLeft;
bool quit = false;

int sudokuAnswers[9][9] = {0}; // Stores answers for Sudoku
int sudokuGrid[9][9] = {0};
bool wrongGrid[9][9]; // Was that square wrong

static int numEnterMode = 1; // What number is placed in the square when square is clicked

SDL_Point windowSize = { .x = 500, .y = 500 };
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

static void MouseClicked(SDL_MouseButtonEvent button);
static void KeyPressed(SDL_KeyboardEvent key);
static void Answers(void);

void Events(void)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        static bool mouseIsDown = false;
        static bool keyIsDown = false;

        if (e.type == SDL_QUIT)
            quit = true;
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN && !mouseIsDown)
            {
                MouseClicked(e.button);
                mouseIsDown = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP && mouseIsDown)
            {
                mouseIsDown = false;
            }
        }
        if (e.type == SDL_KEYDOWN)
        {
            KeyPressed(e.key);
            keyIsDown = true;
        }
        if (e.type == SDL_KEYUP)
        {
            keyIsDown = false;
        }
    }
}

void Draw(void)
{
    SDL_BlitSurface(sudokuGridImg, NULL, screenSurface, NULL);
    SDL_Rect dstrect = { .x = 0, .y = 0, .w = 0, .h = 0 };

    // Size of image for numbers
    dstrect.w = 40;
    dstrect.h = 40;
    // Checks which part of the Sudoku is which number
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (checkAnswersGrid)
            {
                if (sudokuAnswers[x][y] > 0 && sudokuAnswers[x][y] < 10)
                {
                    // Not 25 because the number image is 40 pixels and
                    // the squares are 50 pixels big
                    dstrect.x = x * 50 + 30;
                    dstrect.y = y * 50 + 30;

                    SDL_BlitSurface(nums[sudokuAnswers[x][y]-1], NULL, screenSurface, &dstrect);
                }
            }
            else
            {
                if (sudokuGrid[x][y] > 0 && sudokuGrid[x][y] < 10)
                {
                    // Not 25 because the number image is 40 pixels and
                    // the squares are 50 pixels big
                    dstrect.x = x * 50 + 30;
                    dstrect.y = y * 50 + 30;

                    // Is right answer
                    if (wrongGrid[x][y]) // Right
                        SDL_BlitSurface(nums[sudokuGrid[x][y]-1], NULL, screenSurface, &dstrect);
                    else // Wrong
                    {
                        SDL_BlitSurface(redNums[sudokuAnswers[x][y]-1], NULL, screenSurface, &dstrect);
                    }
                }
            }
        }
    }

    SDL_UpdateWindowSurface(window);
}

void CleanUp(void)
{
    FreeAssets();
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);
}

static void MouseClicked(SDL_MouseButtonEvent button)
{
    printf("Mouse clicked at: %d, %d\n", button.x, button.y);

    // If inside Sudoku grid
    if (button.x >= 25 &&
        button.y >= 25 &&
        button.x <= 475 &&
        button.y <= 475
        )
    {
        SDL_Point gridPostion;

        // 25 is offset of whitespace of image
        gridPostion.x = (button.x - 25) / 50;
        gridPostion.y = (button.y - 25) / 50;

        // Checks if changing a sqaure and then how many empty squares are left
        if (sudokuGrid[gridPostion.x][gridPostion.y] != numEnterMode)
        {
            if (numEnterMode == 0)
                squaresLeft++;
            else
                squaresLeft--;
        }

        sudokuGrid[gridPostion.x][gridPostion.y] = numEnterMode;

        // Grid is full
        if (!squaresLeft)
            Answers();

        printf("Grid postion: %d, %d\n", gridPostion.x, gridPostion.y);
    }
}

static void KeyPressed(SDL_KeyboardEvent key)
{
    // Choose what number to place
    switch (key.keysym.sym)
    {
    case SDLK_0:
        numEnterMode = 0; // Represents empty square
        break;
    case SDLK_1:
        numEnterMode = 1;
        break;
    case SDLK_2:
        numEnterMode = 2;
        break;
    case SDLK_3:
        numEnterMode = 3;
        break;
    case SDLK_4:
        numEnterMode = 4;
        break;
    case SDLK_5:
        numEnterMode = 5;
        break;
    case SDLK_6:
        numEnterMode = 6;
        break;
    case SDLK_7:
        numEnterMode = 7;
        break;
    case SDLK_8:
        numEnterMode = 8;
        break;
    case SDLK_9:
        numEnterMode = 9;
        break;
    }
}

static void Answers(void)
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (sudokuGrid[x][y] != sudokuAnswers[x][y])
                wrongGrid[x][y] = false;
        }
    }
}
