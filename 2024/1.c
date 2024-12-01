#include <stdio.h>
#include <stdlib.h>

#define MAX_LOC 100000

int main()
{
    FILE *file = fopen("1.txt", "r");

    int locs1[MAX_LOC], locs2[MAX_LOC];
    for (int i = 0; i < MAX_LOC; i++)
    {
        locs1[i] = 0;
        locs2[i] = 0;
    }

    int loc1, loc2;
    while (fscanf(file, "%d %d", &loc1, &loc2) == 2)
    {
        locs1[loc1]++;
        locs2[loc2]++;
    }

    int simScore = 0;
    for (int i = 0; i < MAX_LOC; i++)
    {
        simScore += i * locs1[i] * locs2[i];
    }

    int sumDelta = 0;
    int i1 = 0,
        i2 = 0;
    while (i1 < MAX_LOC && i2 < MAX_LOC)
    {
        if (locs1[i1] == 0)
        {
            i1++;
            continue;
        }

        if (locs2[i2] == 0)
        {
            i2++;
            continue;
        }

        sumDelta += abs(i1 - i2);
        locs1[i1]--;
        locs2[i2]--;
    }

    printf("Star 1 answer is: %d\n", sumDelta); // Expect: 1580061
    printf("Star 2 answer is: %d\n", simScore); // Expect: 23046913

    fclose(file);
}
