#include "sudoku.h"
#include "generator.h"

int main(int argc, char *argv[])
{
    // Seed for random numbers
    time_t t;
    srand((unsigned int)time(&t));

    // Flags and stuff
    for (int i = 1; i < argc; i++)
    {
        if (argv[i] == "-mode")
        {
            if (argv[i+1] == "normal")
                mode = NORMAL_MODE;
            else if (argv[i+1] == "creation")
                mode = CREATION_MODE;
            else if (argv[i+1] == "ai")
                mode = AI_MODE;
            else
                mode = NORMAL_MODE;
        }
        if (argv[i] == "-difficulty")
        {
            diffculty = strtol(argv[i+1], NULL, 0);
        }
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return EXIT_FAILURE;

    window = SDL_CreateWindow("Sudoku",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowSize.x,
                              windowSize.y,
                              0
                              );
    if (window == NULL)
        return EXIT_FAILURE;
    if (!LoadAssets())
        return EXIT_FAILURE;
    screenSurface = SDL_GetWindowSurface(window);

    if (mode != CREATION_MODE)
        CreateSudoku();

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            wrongGrid[x][y] = true;
        }
    }

    while (!quit)
    {
        Events();
        Draw();
    }

    quit = true;
    CleanUp();
    SDL_Quit();
    return EXIT_SUCCESS;
}
