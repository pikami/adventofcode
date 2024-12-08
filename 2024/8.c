#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_ANTENNAS 100
#define MAX_TOTAL_ANTINODES 10000

typedef struct
{
    int x, y;
} Coordinate;

typedef struct
{
    Coordinate position[MAX_ANTENNAS];
    int count;
    char frequency;
} Antenna;

Coordinate allAntinodes[MAX_TOTAL_ANTINODES];
Coordinate p2Antinodes[MAX_TOTAL_ANTINODES];
int allAntinodeCount = 0;
int p2AntinodeCount = 0;

int maxX = 0;
int maxY = 0;

int antennaIndexByFrequency(Antenna antennas[], int antennaCount, char frequency)
{
    for (int i = 0; i < antennaCount; i++)
    {
        if (antennas[i].frequency == frequency)
        {
            return i;
        }
    }

    return -1;
}

int containsCoordinate(Coordinate coordinates[], int count, Coordinate coordinate)
{
    for (int i = 0; i < count; i++)
    {
        if (coordinates[i].x == coordinate.x && coordinates[i].y == coordinate.y)
        {
            return 1;
        }
    }

    return 0;
}

int pointIsInBounds(Coordinate point)
{
    return point.x >= 0 && point.x < maxX && point.y >= 0 && point.y < maxY;
}

void p2placeAntinodesRecursive(Coordinate pos, Coordinate dir)
{
    Coordinate newPos = {
        .x = pos.x + dir.x,
        .y = pos.y + dir.y,
    };

    if (!pointIsInBounds(newPos))
    {
        return;
    }

    if (!containsCoordinate(p2Antinodes, p2AntinodeCount, newPos))
    {
        p2Antinodes[p2AntinodeCount] = newPos;
        p2AntinodeCount++;
    }

    p2placeAntinodesRecursive(newPos, dir);
}

void getAntinodes(Antenna antenna)
{
    for (int i = 0; i < antenna.count; i++)
    {
        Coordinate posA = antenna.position[i];
        for (int j = i + 1; j < antenna.count; j++)
        {
            Coordinate posB = antenna.position[j];

            int xDiff = posB.x - posA.x;
            int yDiff = posB.y - posA.y;

            Coordinate a1 = (Coordinate){posA.x - xDiff, posA.y - yDiff};
            Coordinate a2 = (Coordinate){posB.x + xDiff, posB.y + yDiff};

            if (pointIsInBounds(a1) && !containsCoordinate(allAntinodes, allAntinodeCount, a1))
            {
                allAntinodes[allAntinodeCount] = a1;
                allAntinodeCount++;
            }

            if (pointIsInBounds(a2) && !containsCoordinate(allAntinodes, allAntinodeCount, a2))
            {
                allAntinodes[allAntinodeCount] = a2;
                allAntinodeCount++;
            }

            if (pointIsInBounds(posA) && !containsCoordinate(p2Antinodes, p2AntinodeCount, posA))
            {
                p2Antinodes[p2AntinodeCount] = posA;
                p2AntinodeCount++;
            }
            p2placeAntinodesRecursive(posA, (Coordinate){xDiff, yDiff});
            p2placeAntinodesRecursive(posA, (Coordinate){-xDiff, -yDiff});
        }
    }
}

int main()
{
    FILE *file = fopen("8.txt", "r");
    Antenna antennas[MAX_ANTENNAS] = {0};
    int antennaCount = 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        for (int i = 0; i < strlen(line); i++)
        {
            if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= '0' && line[i] <= '9'))
            {
                int antennaIndex = antennaIndexByFrequency(antennas, antennaCount, line[i]);
                if (antennaIndex == -1)
                {
                    antennaIndex = antennaCount;
                    antennaCount++;
                }

                int positionIndex = antennas[antennaIndex].count;
                antennas[antennaIndex].position[positionIndex].x = i;
                antennas[antennaIndex].position[positionIndex].y = maxY;
                antennas[antennaIndex].frequency = line[i];
                antennas[antennaIndex].count++;
            }
        }
        maxY++;
        maxX = strlen(line) - 1;
    }

    for (int i = 0; i < antennaCount; i++)
    {
        getAntinodes(antennas[i]);
    }

    printf("Star 1 answer is: %d\n", allAntinodeCount); // Expect: 311
    printf("Star 2 answer is: %d\n", p2AntinodeCount);  // Expect: 1115

    fclose(file);
}
