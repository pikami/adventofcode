#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 2000

long generateNext(long current)
{
    long result = current * 64;
    result = result ^ current;
    result = result % 16777216;
    current = result;

    result = result / 32;
    result = result ^ current;
    result = result % 16777216;
    current = result;

    result = result * 2048;
    result = result ^ current;
    result = result % 16777216;

    return result;
}

long generateNth(long current, int n)
{
    for (int i = 0; i < n; i++)
    {
        current = generateNext(current);
    }
    return current;
}

int main()
{
    FILE *file = fopen("22.txt", "r");
    long initialNumbers[MAX_LINES];
    int numCount = 0;
    while (fscanf(file, "%ld", &initialNumbers[numCount]) == 1)
    {
        numCount++;
    }
    free(file);

    unsigned long long sum = 0;
    for (int i = 0; i < numCount; i++)
    {
        sum += generateNth(initialNumbers[i], 2000);
        // printf("%ld: %ld\n", initialNumbers[i], generateNth(initialNumbers[i], 2000));
    }

    printf("Star 1 answer is: %llu\n", sum); // Expect: 14869099597
}
