#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 13
#define MAX_LINES 1001

int getLFS(char input[MAX_LINES][MAX_LEN], int lineCnt, int bitLen);

int main(void)
{
  FILE* file = fopen ("day3.txt", "r");
  char input[MAX_LINES][MAX_LEN];
  int activeBitCnt[MAX_LEN],
      lineCnt = 0,
      bitLen = 0;

  // Read data and count active bits
  while (fscanf (file, "%[^\n]\n", &input[lineCnt]) > 0)
  {
    for (int i = 0; i < MAX_LEN; i++) {
      if (input[lineCnt][i] == '1') activeBitCnt[i]++;
    }

    lineCnt++;
  }
  fclose (file);
  bitLen = strlen(input[lineCnt - 1]);

  // Calculate gama and epsilon
  int base = 1,
      gamma = 0,
      epsilon = 0;
  for (int i = bitLen - 1; i >= 0; i--) {
    if (lineCnt - activeBitCnt[i] > ceil(lineCnt / 2)) {
      epsilon += base;
    } else {
      gamma += base;
    }
    base *= 2;
  }

  int lfs = getLFS(input, lineCnt, bitLen);
  printf ("Star 1 answer is: %d\n", gamma * epsilon);
  printf ("Star 2 answer is: %d\n", lfs);
}

// Calculates life support rating
int getLFS(char input[MAX_LINES][MAX_LEN], int lineCnt, int bitLen)
{
  // o2 generator
  int o2cnt1 = 0,
      o2validBits = 0,
      o2validLines = lineCnt,
      o2dec = 0;
  char o2bin[MAX_LEN];

  // co2 scrubber
  int co2cnt1 = 0,
      co2validBits = 0,
      co2validLines = lineCnt,
      co2dec = 0;
  char co2bin[MAX_LEN];

  for (int bit = 0; bit < bitLen; bit++) {
    o2cnt1 = 0;
    co2cnt1 = 0;

    for (int line = 0; line < lineCnt; line++) {
      o2validBits = 1;
      co2validBits = 1;

      for (int i = 0; i < bit; i++) {
        if (input[line][i] != o2bin[i]) {
          o2validBits = 0;
        }

        if (input[line][i] != co2bin[i]) {
          co2validBits = 0;
        }

        if (o2validBits + co2validBits < 1) {
          break;
        }
      }

      if (o2validBits == 1 && input[line][bit] == '1') o2cnt1++;
      if (co2validBits == 1 && input[line][bit] == '1') co2cnt1++;
    }

    if (o2validLines - o2cnt1 <= ceil(o2validLines / 2)) {
      o2bin[bit] = '1';
      o2validLines = o2cnt1;
      o2dec += pow(2, bitLen - bit - 1);
    } else {
      o2bin[bit] = '0';
      o2validLines -= o2cnt1;
    }

    if (co2validLines - co2cnt1 >= ceil(co2validLines / 2)
      && co2validLines - co2cnt1 != co2cnt1 && co2cnt1 > 0) {
      co2bin[bit] = '1';
      co2validLines = co2cnt1;
      co2dec += pow(2, bitLen - bit - 1);
    } else {
      co2bin[bit] = '0';
      co2validLines -= co2cnt1;
    }
  }

  return o2dec * co2dec;
}