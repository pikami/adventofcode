#include <stdio.h>
#include <string.h>

#define MAX_DAYS 11
#define FIRST_STAR 80
#define SECOND_STAR 256

int main(void)
{
  FILE* file = fopen ("day6.txt", "r");
  long buff = 0,
      cnt1 = 0,
      cnt2 = 0,
      fishies[MAX_DAYS] = { 0 };

  // Read draws
  while (fscanf (file, "%d,", &buff) > 0) {
    fishies[buff]++;
  }

  // Simulate
  for (int day = 0; day < SECOND_STAR; day++) {
    fishies[9] += fishies[0];
    fishies[7] += fishies[0];

    for (int i = 0; i < MAX_DAYS - 1; i++) {
      fishies[i] = fishies[i + 1];
    }

    if (day == FIRST_STAR - 1) {
      // Calculate first star
      for (int i = 0; i < MAX_DAYS; i++) {
        cnt1 += fishies[i];
      }
    }
  }

  // Calculate second star
  for (int i = 0; i < MAX_DAYS; i++) {
    cnt2 += fishies[i];
  }

  printf ("Star 1 answer is: %ld\n", cnt1);
  printf ("Star 2 answer is: %ld\n", cnt2);

  fclose (file);
}
