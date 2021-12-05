#include <stdio.h>
#include <string.h>

#define GRID_X 1000
#define GRID_Y 1000
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int run(int enableDiagonals);

int main(void)
{
  printf ("Star 1 answer is: %d\n", run(0));
  printf ("Star 2 answer is: %d\n", run(1));
}

int run(int enableDiagonals)
{
  FILE* file = fopen ("day5.txt", "r");
  int grid[GRID_X * GRID_Y] = { 0 },
      x1, y1, x2, y2,
      cnt = 0;

  while (fscanf (file, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) > 0) {
    cnt++;
    if (x1 == x2 || y1 == y2) { // horizontal / vertical
      for (int y = MIN(y1, y2); y <= MAX(y1, y2); y++) {
        for (int x = MIN(x1, x2); x <= MAX(x1, x2); x++) {
          grid[GRID_X * y + x]++;
        }
      }
    } else if (enableDiagonals) { // diagonal
      if (y1 > y2) {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
        tmp = x2;
        x2 = x1;
        x1 = tmp;
      }

      int x = x1;
      for (int y = MIN(y1, y2); y <= MAX(y1, y2); y++) {
        grid[GRID_X * y + x]++;
        if (x1 < x2) x++;
        else x--;
      }
    }
  }

  int overlaps = 0;
  for (int i = 0; i < GRID_X * GRID_Y; i++) {
    if (grid[i] > 1) {
      overlaps++;
    }
  }

  fclose (file);
  return overlaps;
}
