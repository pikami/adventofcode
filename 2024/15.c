#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_MOVES 30000

typedef struct
{
    int lineCount, colCount;
} FileStats;

typedef struct
{
    int x, y;
} Vector;

FileStats getFileStats(FILE *file);
Vector getDirection(char move);
void executeMove(char **grid, FileStats stats, Vector *position, char move);
void printGrid(char **grid, FileStats stats);
Vector findStart(char **grid, FileStats stats);
int calculateGpsScore(char **grid, FileStats stats);

int main()
{
    FILE *file = fopen("15ex.txt", "r");
    char line[MAX_LINE];
    FileStats stats = getFileStats(file);

    char **grid = malloc(stats.lineCount * sizeof(char *));
    for (int i = 0; i < stats.lineCount; i++)
    {
        grid[i] = malloc((stats.colCount + 1) * sizeof(char));
        fgets(grid[i], stats.colCount + 1, file);
    }

    char moves[MAX_MOVES];
    while (fgets(line, sizeof(line), file))
    {
        int currentMoves = strlen(moves);
        if (moves[currentMoves - 1] == '\n')
        {
            currentMoves--;
        }
        if (currentMoves + strlen(line) > MAX_MOVES)
        {
            printf("MAX_MOVES is too smol :P\n");
            free(grid);
            fclose(file);
            break;
        }
        strcpy(moves + currentMoves, line);
    }

    Vector position = findStart(grid, stats);
    for (int i = 0; i < strlen(moves); i++)
    {
        executeMove(grid, stats, &position, moves[i]);
        // getchar();
        // printGrid(grid, stats);
    }

    int gpsScore = calculateGpsScore(grid, stats);
    printf("Star 1 answer is: %d\n", gpsScore); // Expect: 1485257

    free(grid);
    fclose(file);
}

FileStats getFileStats(FILE *file)
{
    FileStats stats = {0, 0};
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        int lineLength = strlen(line);
        stats.lineCount++;
        if (stats.colCount == 0)
        {
            stats.colCount = lineLength;
        }
        if (lineLength == 1)
        {
            break;
        }
    }
    rewind(file);
    return stats;
}

Vector getDirection(char move)
{
    Vector direction = {0, 0};
    switch (move)
    {
    case '^':
        direction.y = -1;
        break;
    case 'v':
        direction.y = 1;
        break;
    case '<':
        direction.x = -1;
        break;
    case '>':
        direction.x = 1;
        break;
    default:
        break;
    }
    return direction;
}

void executeMove(char **grid, FileStats stats, Vector *position, char move)
{
    Vector direction = getDirection(move);
    int newX = position->x + direction.x;
    int newY = position->y + direction.y;
    if (grid[newY][newX] == '#')
    {
        return;
    }

    if (grid[newY][newX] == 'O')
    {
        executeMove(grid, stats, &(Vector){.x = newX, .y = newY}, move);
    }

    if (grid[newY][newX] == '.')
    {
        grid[newY][newX] = grid[position->y][position->x];
        grid[position->y][position->x] = '.';
        position->x = newX;
        position->y = newY;
    }
}

void printGrid(char **grid, FileStats stats)
{
    for (int i = 0; i < stats.lineCount; i++)
    {
        printf("%s", grid[i]);
    }
}

Vector findStart(char **grid, FileStats stats)
{
    for (int y = 0; y < stats.lineCount; y++)
    {
        for (int x = 0; x < stats.colCount; x++)
        {
            if (grid[y][x] == '@')
            {
                return (Vector){.x = x, .y = y};
            }
        }
    }

    printf("No start found\n");
    return (Vector){.x = -1, .y = -1};
}

int calculateGpsScore(char **grid, FileStats stats)
{
    int score = 0;
    for (int y = 0; y < stats.lineCount; y++)
    {
        for (int x = 0; x < stats.colCount; x++)
        {
            if (grid[y][x] == 'O')
            {
                score += y * 100 + x;
            }
        }
    }
    return score;
}
