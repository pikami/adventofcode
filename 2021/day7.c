#include <stdio.h>
#include <string.h>

#define MAX_CRABS 10000
#define ABS(x) (((x) < 0) ? -(x) : (x))

int main(void)
{
  FILE* file = fopen ("day7.txt", "r");
  int pos[MAX_CRABS] = { 0 },
      cnt = 0;

  // Read crabs
  while (fscanf (file, "%d,", &pos[cnt]) > 0) {
    cnt++;
  }

  // Min / Max pos
  int min = 0,
      max = 0;
  for (int i = 0; i < cnt; i++) {
    if (pos[i] > max) max = pos[i];
    if (pos[i] < min || i == 0) min = pos[i];
  }

  // Find cheapest pos
  int currCostS1 = 0,
      currCostS2 = 0,
      minCostS1 = 0,
      minCostS2 = 0;
  for (int i = min; i < max; i++) {
    currCostS1 = currCostS2 = 0;

    for (int c = 0; c < cnt; c++) {
      int fuel = ABS(pos[c] - i);
      currCostS1 += fuel;
      currCostS2 += (fuel * fuel + fuel) / 2;
    }

    if (minCostS1 > currCostS1 || i == 0) {
      minCostS1 = currCostS1;
    }

    if (minCostS2 > currCostS2 || i == 0) {
      minCostS2 = currCostS2;
    }
  }

  printf ("Star 1 answer is: %d\n", minCostS1);
  printf ("Star 2 answer is: %d\n", minCostS2);

  fclose (file);
}
