#include <stdio.h>
#include <stdlib.h>

#define MAX_WINDOW 4096

int main(void)
{
  FILE* file = fopen ("day1.txt", "r");
  int curr = 0,
      prev = 0,
      result1 = 0;
  int n = 1,
      windows[MAX_WINDOW],
      result2 = 0;

  for (int i = 0; i < MAX_WINDOW; i++) {
    windows[i] = 0;
  }

  fscanf (file, "%d", &curr);
  windows[0] = curr;
  windows[1] = curr;
  windows[2] = curr;

  while (!feof (file))
  {
    prev = curr;

    fscanf (file, "%d", &curr);

    if (curr > prev) {
      result1++;
    }

    windows[n] += curr;
    windows[n+1] += curr;
    windows[n+2] += curr;

    n++;
  }

  for (int i = 3; i < n - 1; i++) {
    if (windows[i-1] < windows[i]) {
      result2++;
    }
  }

  printf ("Star 1 answer is: %d\n", result1);
  printf ("Star 2 answer is: %d\n", result2);

  fclose (file);
}
