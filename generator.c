#include "generator.h"

static void Generate(void);
static void Hide(void);

static bool CheckColumn(int cellPosX, int cellPosY, int tempNum);
static bool CheckRow(int cellPosX, int cellPosY, int tempNum);
static bool CheckSquare(int cellPosX, int cellPosY, int tempNum);
static void RemoveElement(int pos);

// The public function which is called
void CreateSudoku(void)
{
    Generate();
    Hide();
    printf("Sudoku generated!");
}

static int avaliableNums[9];
static int size;
static void ResetAvaliableNums(void)
{
    size = 9;
    for (int i = 0; i < size; i++)
        avaliableNums[i] = i + 1;
}

// Not very efficent
static void Generate(void)
{
    for (int x = 0; x < 9; x++)
    {
        ResetAvaliableNums();
        /* If the loop fails to many times, reset it
         * This is to prevent infinite loops with failed
         * This is where a number is the last one left
         * But it cannot be placed because it fails the logic
         * As there is already a number in the square or row
        */
        for (int y = 0; y < 9; y++)
        {
            int iterationNum = 0;
            // 0-8 not 1-9 due to array
            int tempCell;
            do
            {
                if ((++iterationNum) > 20)
                {
                    ResetAvaliableNums();
                    y = 0;
                    iterationNum = 0;
                    for (int i = 0; i < 9; i++)
                        sudokuAnswers[x][i] = 0;
                }
                int numToErasePos = rand() % 9; // Array index
                tempCell = avaliableNums[numToErasePos];
                if (CheckColumn(x, y, tempCell) &&
                    CheckRow(x, y, tempCell) &&
                    CheckSquare(x, y, tempCell)
                    )
                {
                    sudokuAnswers[x][y] = tempCell;
                    tempCell = 0;
                    RemoveElement(numToErasePos);
                }
            } while (tempCell > 0);
            Draw();
        }
    }
}

static void Hide(void)
{
    // How many square are hidden
    int hiddenSquares = diffculty;
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            //printf("Is hidden: %d\n", (rand() % 82));
            sudokuGrid[x][y] = (rand() % 82 <= hiddenSquares) ? 0 : sudokuAnswers[x][y];
            if (sudokuGrid[x][y] == 0)
                squaresLeft++;
        }
    }

}

static bool CheckColumn(int cellPosX, int cellPosY, int tempNum)
{
    for (int y = 0; y < 9; y++)
    {
        if (sudokuAnswers[cellPosX][y] == tempNum)
        {
            return false;
        }
    }
    return true;
}

// Problem is here
static bool CheckRow(int cellPosX, int cellPosY, int tempNum)
{
    for (int x = 0; x < 9; x++)
    {
        if (sudokuAnswers[x][cellPosY] == tempNum)
        {
            return false;
        }
    }
    return true;
}

// Checking not working
static bool CheckSquare(int cellPosX, int cellPosY, int tempNum)
{
    int xSquare;
    int ySquare;

    // This logic tests to see which vertical/horizontal square the cell falls into
    // It tests bottom/right to top/left and uses 5 and 2 in cells 0-8
    if (cellPosX - 5 > 0)
        xSquare = 2;
    else if (cellPosX - 2 > 0)
        xSquare = 1;
    else
        xSquare = 0;

    if (cellPosY - 5 > 0)
        ySquare = 2;
    else if (cellPosY - 2 > 0)
        ySquare = 1;
    else
        ySquare = 0;

    // This loops through all cells in the square
    for (int x = xSquare*3; x <= (xSquare*3)+2; x++)
    {
        for (int y = ySquare*3; y <= (ySquare*3)+2; y++)
        {
            if (sudokuAnswers[x][y] == tempNum)
            {
                return false;
            }

        }
    }
    return true;
}

static void RemoveElement(int pos)
{
    // Not referenced to original
    int tempArr[9];
    for (int i = 0; i < size; i++)
        tempArr[i] = avaliableNums[i];

    for (int i = pos; i < size; i++)
    {
        if (i < size-1)
            avaliableNums[i] = tempArr[i+1];
    }
    size--;
}
