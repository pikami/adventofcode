#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1024
#define MAX_LINES 1000
#define MAX_NUMBERS 1000

struct Equation
{
    long long expected;
    int numberCount;
    int numbers[MAX_NUMBERS];
};

long long concat(long long a, long long b)
{
    long long c = b;
    while (c > 0)
    {
        a *= 10;
        c /= 10;
    }
    return a + b;
}

int isSolvable(struct Equation equation, int index, long long current, int enableConcat)
{
    if (index == equation.numberCount)
    {
        return current == equation.expected;
    }

    return isSolvable(equation, index + 1, current + equation.numbers[index], enableConcat) ||
           isSolvable(equation, index + 1, current * equation.numbers[index], enableConcat) ||
           (enableConcat && isSolvable(equation, index + 1, concat(current, equation.numbers[index]), enableConcat));
}

int main()
{
    FILE *file = fopen("7r.txt", "r");

    int equationCount = 0;
    struct Equation *equations = malloc(MAX_LINES * sizeof(struct Equation));

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ": ");
        equations[equationCount].expected = atoll(token);

        equations[equationCount].numberCount = 0;
        while ((token = strtok(NULL, " ")) != NULL)
        {
            equations[equationCount].numbers[equations[equationCount].numberCount] = atoi(token);
            equations[equationCount].numberCount++;
        }

        equationCount++;
    }

    unsigned long long sumTestNumbers = 0;
    unsigned long long sumTestNumbersWithConcat = 0;
    for (int i = 0; i < equationCount; i++)
    {
        if (isSolvable(equations[i], 1, equations[i].numbers[0], 0))
        {
            sumTestNumbers += equations[i].expected;
        }

        if (isSolvable(equations[i], 1, equations[i].numbers[0], 1))
        {
            sumTestNumbersWithConcat += equations[i].expected;
        }
    }

    printf("Star 1 answer is: %llu\n", sumTestNumbers);           // Expect: 1708857123053
    printf("Star 2 answer is: %llu\n", sumTestNumbersWithConcat); // Expect: 189207836795655

    free(equations);
    fclose(file);
}