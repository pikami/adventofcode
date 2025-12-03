input = ``;

getBig = (line, N) => line
  .split("")
  .reduce((a, c, i) => {
    for (j = 0; j < N; j++) {
      if (c > a[j] && line.length - i >= N - j) {
        a[j] = c;
        a.fill(0, j + 1);
        break;
      }
    }
    return a;
  }, Array(N).fill(0))
  .join("");

console.log(
  input.split("\n")
    .map((line) => parseInt(getBig(line, 2)))
    .reduce((a, x) => a + x, 0)
);

console.log(
  input.split("\n")
    .map((line) => parseInt(getBig(line, 12)))
    .reduce((a, x) => a + x, 0)
);
