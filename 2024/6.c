#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_LINES 1000
#define DIRECTIONS 4

struct Guard
{
    int x, y;
    int dir;
    int inf;
    int hasObsticle;
    int ***visited;
    char **grid;
};

struct Vector
{
    int x, y;
};

int lineCount = 0, colCount = 0, loopCount = 0;
char **grid;

struct Vector foundLoops[MAX_LINES * MAX_LINES] = {0};
struct Vector directions[] = {
    {.x = 0, .y = -1}, // Up
    {.x = 1, .y = 0},  // Right
    {.x = 0, .y = 1},  // Down
    {.x = -1, .y = 0}  // Left
};

void initializeGuard(struct Guard *guard);
void printGrid(struct Guard guard);
void findGuard(struct Guard *guard);
void rotateGuard(struct Guard *guard);
int countVisited(struct Guard guard);
struct Guard cloneGuard(struct Guard guard);
int ***initializeVisited(int rows, int cols);
char **initializeGrid(int rows, int cols);
void freeGuard(struct Guard guard);
void addLoop(int x, int y);
int hasLoop(int x, int y);
int runGuard(struct Guard *guard);

int main()
{
    FILE *file = fopen("6.txt", "r");
    grid = malloc(MAX_LINES * sizeof(char *));

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        if (colCount == 0)
        {
            colCount = strlen(line);
        }

        grid[lineCount] = malloc((colCount + 1) * sizeof(char));
        strcpy(grid[lineCount], line);
        lineCount++;
    }
    colCount--;

    struct Guard guard;
    initializeGuard(&guard);
    runGuard(&guard);
    printGrid(guard);
    int visited = countVisited(guard);
    freeGuard(guard);

    printf("Star 1 answer is: %d\n", visited);   // Expect: 4663
    printf("Star 2 answer is: %d\n", loopCount); // Expect: 1530

    for (int i = 0; i < lineCount; i++)
    {
        free(grid[i]);
    }
    free(grid);
    fclose(file);
}

int runGuard(struct Guard *guard)
{
    int guardInBounds = 1;
    guard->grid[guard->y][guard->x] = 'X';
    while (guardInBounds)
    {
        int newX = guard->x + directions[guard->dir].x,
            newY = guard->y + directions[guard->dir].y;
        guardInBounds = newX < colCount && newX >= 0 && newY < lineCount && newY >= 0;
        if (!guardInBounds)
        {
            break;
        }

        if (guard->visited[newY][newX][guard->dir])
        {
            // infinite loop detected
            return -1;
        }

        if (guard->grid[newY][newX] == '#')
        {
            rotateGuard(guard);
        }
        else
        {
            if (!guard->hasObsticle && !hasLoop(newX, newY))
            {
                struct Guard newGuard;
                initializeGuard(&newGuard);
                newGuard.grid[newY][newX] = '#';
                newGuard.hasObsticle = 1;
                int obsticleResult = runGuard(&newGuard);
                if (obsticleResult == -1)
                {
                    addLoop(newX, newY);
                    printf("Obsticle causes infinite loop (%d;%d)\n", newX, newY);
                }
                freeGuard(newGuard);
            }

            guard->visited[newY][newX][guard->dir] = 1;
            guard->grid[newY][newX] = 'X';
            guard->x = newX;
            guard->y = newY;
        }
    }
    return 0;
}

void printGrid(struct Guard guard)
{
    for (int x = 0; x < lineCount; x++)
    {
        printf("%s\n", guard.grid[x]);
    }
}

void rotateGuard(struct Guard *guard)
{
    switch (guard->dir)
    {
    case 0:
        guard->dir = 1;
        break;
    case 1:
        guard->dir = 2;
        break;
    case 2:
        guard->dir = 3;
        break;
    case 3:
        guard->dir = 0;
        break;
    default:
        break;
    }
}

void findGuard(struct Guard *guard)
{
    for (int x = 0; x < colCount; x++)
    {
        for (int y = 0; y < lineCount; y++)
        {
            switch (guard->grid[y][x])
            {
            case '^':
                guard->x = x;
                guard->y = y;
                guard->dir = 0;
                return;
            case 'v':
                guard->x = x;
                guard->y = y;
                guard->dir = 2;
                return;
            case '<':
                guard->x = x;
                guard->y = y;
                guard->dir = 3;
                return;
            case '>':
                guard->x = x;
                guard->y = y;
                guard->dir = 1;
                return;
            default:
                break;
            }
        }
    }
}

int countVisited(struct Guard guard)
{
    int count = 0;
    for (int x = 0; x < colCount; x++)
    {
        for (int y = 0; y < lineCount; y++)
        {
            if (guard.grid[y][x] == 'X')
            {
                count++;
            }
        }
    }
    return count;
}

int ***initializeVisited(int rows, int cols)
{
    int ***visited = (int ***)malloc(rows * sizeof(int **));
    for (int y = 0; y < rows; y++)
    {
        visited[y] = (int **)malloc(cols * sizeof(int *));
        for (int x = 0; x < cols; x++)
        {
            visited[y][x] = (int *)calloc(DIRECTIONS, sizeof(int));
        }
    }
    return visited;
}

char **initializeGrid(int rows, int cols)
{
    if (grid == NULL)
    {
        return NULL;
    }

    char **newGrid = (char **)malloc(rows * sizeof(char *));
    if (newGrid == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        newGrid[i] = (char *)malloc((cols + 1) * sizeof(char));
        memcpy(newGrid[i], grid[i], cols * sizeof(char));
    }
    return newGrid;
}

void initializeGuard(struct Guard *guard)
{
    guard->x = 0;
    guard->y = 0;
    guard->dir = 0;
    guard->inf = 0;
    guard->hasObsticle = 0;
    guard->visited = initializeVisited(colCount, lineCount);
    guard->grid = initializeGrid(lineCount, colCount);
    findGuard(guard);
}

void freeGuard(struct Guard guard)
{
    for (int y = 0; y < lineCount; y++)
    {
        for (int x = 0; x < colCount; x++)
        {
            free(guard.visited[y][x]);
        }
        free(guard.visited[y]);
        free(guard.grid[y]);
    }
    free(guard.visited);
    free(guard.grid);
}

void addLoop(int x, int y)
{
    for (int i = 0; i < loopCount; i++)
    {
        if (foundLoops[i].x == x && foundLoops[i].y == y)
        {
            return;
        }
    }

    foundLoops[loopCount].x = x;
    foundLoops[loopCount].y = y;
    loopCount++;
}

int hasLoop(int x, int y)
{
    for (int i = 0; i < loopCount; i++)
    {
        if (foundLoops[i].x == x && foundLoops[i].y == y)
        {
            return 1;
        }
    }
    return 0;
}
