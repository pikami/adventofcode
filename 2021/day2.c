#include <stdio.h>

int main(void)
{
  FILE* file = fopen ("day2.txt", "r");
  char cmd[10];
  int cmd_op = 0,
      h = 0,
      d = 0;
  int aim = 0,
      d2 = 0;

  while (fscanf (file,"%s %d", &cmd, &cmd_op) > 0)
  {
    switch (cmd[0]) {
      case 'f':
        h += cmd_op;
        d2 += aim * cmd_op;
        break;

      case 'u':
        d -= cmd_op;
        aim -= cmd_op;
        break;

      case 'd':
        d += cmd_op;
        aim += cmd_op;
        break;
    }
  }

  printf ("Star 1 answer is: %d\n", h * d);
  printf ("Star 2 answer is: %d\n", h * d2);

  fclose (file);
}
