input = ``;

map = input.split("\n").map((line) => line.split(""));
maxX = map[0].length;
maxY = map.length;

isPaper = (x, y) => {
  if (x < 0) return false;
  if (y < 0) return false;
  if (x >= maxX) return false;
  if (y >= maxY) return false;
  return map[y][x] == "@";
};

iter = () => {
  cnts = Array(maxY)
    .fill(0)
    .map(() => Array(maxX).fill(-1));

  for (y = 0; y < maxY; y++) {
    for (x = 0; x < maxX; x++) {
      if (map[y][x] != "@") continue;
      cnts[y][x] = 0;
      if (isPaper(x - 1, y)) cnts[y][x]++;
      if (isPaper(x + 1, y)) cnts[y][x]++;
      if (isPaper(x, y - 1)) cnts[y][x]++;
      if (isPaper(x, y + 1)) cnts[y][x]++;
      if (isPaper(x - 1, y - 1)) cnts[y][x]++;
      if (isPaper(x + 1, y - 1)) cnts[y][x]++;
      if (isPaper(x - 1, y + 1)) cnts[y][x]++;
      if (isPaper(x + 1, y + 1)) cnts[y][x]++;
    }
  }

  for (y = 0; y < maxY; y++) {
    for (x = 0; x < maxX; x++) {
      if (map[y][x] != "@") continue;
      if (cnts[y][x] >= 0 && cnts[y][x] < 4) {
        map[y][x] = "x";
      }
    }
  }

  return cnts.flat().filter((x) => x >= 0 && x < 4).length;
};

total = 0;
for (i = 0; true; i++) {
  c = iter();
  total += c;
  if (i == 0) {
    console.log(c);
  }
  if (c == 0) break;
}
console.log(total);
