#include <stdio.h>
#include <string.h>

#define MAX_DRAWS 100
#define GRID_X 5
#define GRID_Y 5
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int main(void)
{
  FILE* file = fopen ("day4.txt", "r");
  int draws[MAX_DRAWS] = { -1 };
  int drawCount = 0,
      winningBoardScore = 0,
      winningBoardMoves = MAX_DRAWS + 1,
      losingBoardScore = 0,
      losingBoardMoves = 0;

  // Read draws
  while (fscanf (file, "%d", &draws[drawCount]) > 0) {
    drawCount++;
    if (fgetc(file) == '\n') {
      break;
    }
  }

  // Read tables one-by-one
  int doneReading = 0;
  while (doneReading != 1) {
    int grid[GRID_Y * GRID_X];
    for (int gi = 0; gi < GRID_Y * GRID_X; gi++) {
      if (fscanf (file, "%d", &grid[gi]) < 1) {
        doneReading = 1;
      }
    }
    if (doneReading == 1) break;

    int win[GRID_Y + GRID_X] = { 0 };
    for (int i = 0; i < drawCount; i++) {
      for (int gi = 0; gi < GRID_Y * GRID_X; gi++) {
        if (grid[gi] == draws[i]) {
          win[gi / GRID_Y]++;
          win[GRID_Y + gi % GRID_X]++;
          grid[gi] = -1;

          if (win[gi / GRID_Y] == GRID_Y
            || win[GRID_Y + gi % GRID_X] == GRID_X) {

            int unmarkedSum = 0;
            for (int gi = 0; gi < GRID_Y * GRID_X; gi++) {
              unmarkedSum += MAX(0, grid[gi]);
            }

            if (winningBoardMoves > i) {
              winningBoardMoves = i;
              winningBoardScore = unmarkedSum * draws[i];
            }

            if (losingBoardMoves < i) {
              losingBoardMoves = i;
              losingBoardScore = unmarkedSum * draws[i];
            }

            // finish work on current grid
            i = drawCount;
          }
        }
      }
    }
  }

  printf ("Star 1 answer is: %d\n", winningBoardScore);
  printf ("Star 2 answer is: %d\n", losingBoardScore);

  fclose (file);
}
