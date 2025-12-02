input = ``;
ranges = input.split(",").map((range) => {
  const [start, end] = range.split("-").map(Number);
  return { start, end };
});

set1 = new Set();
set2 = new Set();
max = ranges.reduce((acc, { end }) => Math.max(acc, end), 0);
maxLen = max.toString().length;

for (chars = 1; chars <= maxLen / 2; chars++) {
  min = Math.pow(10, chars - 1);
  max = Math.pow(10, chars) - 1;
  maxReps = Math.floor(maxLen / chars);
  for (i = min; i <= max; i++) {
    for (reps = 2; reps <= maxReps; reps++) {
      num = parseInt(i.toString().repeat(reps));
      if (ranges.some(({ start, end }) => start <= num && num <= end)) {
        if (reps == 2) set1.add(num);
        set2.add(num);
      }
    }
  }
}

console.log(Array.from(set1).reduce((x, a) => x + a, 0))
console.log(Array.from(set2).reduce((x, a) => x + a, 0))
