#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_LINE_NUM 100

int read(char **ptr)
{
    int curr;
    if (sscanf(*ptr, "%d", &curr) != 1)
    {
        return -1;
    }

    while (**ptr && (**ptr != ' ' && **ptr != '\n'))
    {
        (*ptr)++;
    }
    while (**ptr == ' ')
    {
        (*ptr)++;
    }

    return curr;
}

int safe(int lvls[], int cnt, int skip)
{
    int prev, curr = -1, prevDiff = 69420, curDiff;
    for (int i = 0; i < cnt; i++)
    {
        if (i == skip)
        {
            continue;
        }

        if (curr == -1)
        {
            curr = lvls[i];
            continue;
        }

        prev = curr;
        curr = lvls[i];
        curDiff = prev - curr;
        if (curDiff == 0 || abs(curDiff) > 3 || (prevDiff != 69420 && curDiff * prevDiff < 0))
        {
            return 0;
        }
        prevDiff = curDiff;
    }

    return 1;
}

int main()
{
    FILE *file = fopen("2.txt", "r");

    int safeCnt = 0, safeWithDampner = 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file))
    {
        char *ptr = line;
        int cnt = 0;
        int lvls[MAX_LINE_NUM] = {[0 ... MAX_LINE_NUM - 1] = -1};
        for (cnt = 0; ((lvls[cnt] = read(&ptr)) != -1); cnt++)
        {
        }

        for (int i = -1; i < cnt; i++)
        {
            int isSafe = safe(lvls, cnt, i);
            if (isSafe)
            {
                if (i == -1)
                {
                    safeCnt++;
                }
                safeWithDampner++;
                printf(line);
                break;
            }
        }
    }

    printf("Star 1 answer is: %d\n", safeCnt);         // Expect: 402
    printf("Star 2 answer is: %d\n", safeWithDampner); // Expect: 455
}