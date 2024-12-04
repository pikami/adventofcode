#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_LINES 1000

int lineCount = 0, rowCount = 0;

// ^ ^> > V> V <V < <^
int searchDir(char **grid, int x, int y, int dir)
{
    if (dir == 0)
    {
        return y + 3 < lineCount         //
               && grid[y + 1][x] == 'M'  //
               && grid[y + 2][x] == 'A'  //
               && grid[y + 3][x] == 'S'; //
    }
    if (dir == 1)
    {
        return y + 3 < lineCount && x + 3 < rowCount //
               && grid[y + 1][x + 1] == 'M'          //
               && grid[y + 2][x + 2] == 'A'          //
               && grid[y + 3][x + 3] == 'S';         //
    }
    if (dir == 2)
    {
        return strncmp(grid[y] + x, "XMAS", 4) == 0;
    }
    if (dir == 3)
    {
        return y - 3 > -1 && x + 3 < rowCount //
               && grid[y - 1][x + 1] == 'M'   //
               && grid[y - 2][x + 2] == 'A'   //
               && grid[y - 3][x + 3] == 'S';  //
    }
    if (dir == 4)
    {
        return y - 3 > -1                //
               && grid[y - 1][x] == 'M'  //
               && grid[y - 2][x] == 'A'  //
               && grid[y - 3][x] == 'S'; //
    }
    if (dir == 5)
    {
        return y - 3 > -1 && x - 3 > -1      //
               && grid[y - 1][x - 1] == 'M'  //
               && grid[y - 2][x - 2] == 'A'  //
               && grid[y - 3][x - 3] == 'S'; //
    }
    if (dir == 6)
    {
        return (x - 3 > -1) && (strncmp(grid[y] + (x - 3), "SAMX", 4) == 0);
    }
    if (dir == 7)
    {
        return y + 3 < lineCount && x - 3 > -1 //
               && grid[y + 1][x - 1] == 'M'    //
               && grid[y + 2][x - 2] == 'A'    //
               && grid[y + 3][x - 3] == 'S';   //
    }
}

int find(char **grid, int x, int y)
{
    if (grid[y][x] != 'X')
    {
        return 0;
    }

    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        if (searchDir(grid, x, y, i))
        {
            cnt++;
        }
    }
    return cnt;
}

int findPart2(char **grid, int x, int y)
{
    if (grid[y][x] != 'A')
    {
        return 0;
    }

    return y > 0 && x > 0 && y + 1 < lineCount && x + 1 < rowCount &&
           (grid[y - 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M'         //
            || grid[y - 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S')     //
           && (grid[y + 1][x - 1] == 'S' && grid[y - 1][x + 1] == 'M'      //
               || grid[y + 1][x - 1] == 'M' && grid[y - 1][x + 1] == 'S'); //
}

int main()
{
    FILE *file = fopen("4.txt", "r");

    char **grid;
    grid = malloc(MAX_LINES * sizeof(char *));

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        if (rowCount == 0)
        {
            rowCount = strlen(line);
        }

        grid[lineCount] = malloc((rowCount + 1) * sizeof(char));
        strcpy(grid[lineCount], line);
        lineCount++;
    }
    rowCount--;

    int count = 0, count2 = 0;
    for (int x = 0; x < rowCount; x++)
    {
        for (int y = 0; y < lineCount; y++)
        {
            count += find(grid, x, y);
            count2 += findPart2(grid, x, y);
        }
    }

    printf("Star 1 answer is: %d\n", count);  // Expect: 2567
    printf("Star 2 answer is: %d\n", count2); // Expect: 2029

    for (int i = 0; i < lineCount; i++)
    {
        free(grid[i]);
    }
    free(grid);
    fclose(file);
}
