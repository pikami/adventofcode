#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef struct
{
    int lineCount, colCount;
} FileStats;

typedef struct
{
    int x, y;
} Vector;

Vector directions[] = {
    {.x = 0, .y = -1}, // Up
    {.x = 1, .y = 0},  // Right
    {.x = 0, .y = 1},  // Down
    {.x = -1, .y = 0}  // Left
};

int ***memo;

FileStats countLines(FILE *file);
void printGrid(char **grid, int lineCount);
Vector findStart(char **grid, int lineCount);
int findPathRecursive(char **grid, int lineCount, int x, int y, int direction, int score);

int main()
{
    FILE *file = fopen("16ex.txt", "r");
    FileStats fileStats = countLines(file);

    char **grid = malloc(fileStats.lineCount * sizeof(char *));
    memo = malloc(fileStats.lineCount * sizeof(int **));
    for (int i = 0; i < fileStats.lineCount; i++)
    {
        grid[i] = malloc((fileStats.colCount + 1) * sizeof(char));
        memo[i] = malloc(fileStats.colCount * sizeof(int *));
        for (int j = 0; j < fileStats.colCount; j++)
        {
            memo[i][j] = malloc(4 * sizeof(int));
            for (int k = 0; k < 4; k++)
            {
                memo[i][j][k] = -1;
            }
        }
        fgets(grid[i], fileStats.colCount + 1, file);
    }

    printGrid(grid, fileStats.lineCount);
    Vector start = findStart(grid, fileStats.lineCount);
    int bestScore = findPathRecursive(grid, fileStats.lineCount, start.x, start.y, 1, 0);
    printf("Star 1 answer is: %d\n", bestScore); // Expect: 135512

    for (int i = 0; i < fileStats.lineCount; i++)
    {
        free(grid[i]);
        for (int j = 0; j < fileStats.colCount; j++)
        {
            free(memo[i][j]);
        }
    }
    free(grid);
    fclose(file);
}

FileStats countLines(FILE *file)
{
    FileStats stats = {0, 0};
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        if (stats.colCount == 0)
        {
            stats.colCount = strlen(line);
        }
        stats.lineCount++;
    }
    rewind(file);
    return stats;
}

void printGrid(char **grid, int lineCount)
{
    for (int i = 0; i < lineCount; i++)
    {
        printf("%s", grid[i]);
    }
}

Vector findStart(char **grid, int lineCount)
{
    Vector start = {0, 0};
    for (int y = 0; y < lineCount; y++)
    {
        for (int x = 0; x < strlen(grid[y]); x++)
        {
            if (grid[y][x] == 'S')
            {
                start.x = x;
                start.y = y;
                return start;
            }
        }
    }
    return start;
}

int findPathRecursive(char **grid, int lineCount, int x, int y, int direction, int score)
{
    if (grid[y][x] == 'E')
    {
        return score;
    }

    if (grid[y][x] == '#')
    {
        return -1;
    }

    if (memo[y][x][direction] != -1 && memo[y][x][direction] <= score)
    {
        return -1;
    }

    memo[y][x][direction] = score;
    grid[y][x] = '#';

    int bestScore = -1;
    for (int i = 0; i < 4; i++)
    {
        int nextScore = score + (i != direction ? 1001 : 1);
        int result = findPathRecursive(grid, lineCount, x + directions[i].x, y + directions[i].y, i, nextScore);
        if (result != -1 && (bestScore == -1 || result < bestScore))
        {
            bestScore = result;
        }
    }

    grid[y][x] = '.';
    return bestScore;
}
