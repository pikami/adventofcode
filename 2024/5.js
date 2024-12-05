var input = ``;

var [i1, i2] = input.split("\n\n");
i1 = i1.split("\n").map((x) => x.split("|"));
i2 = i2.split("\n").map((x) => x.split(","));

var badLines = [];
var star1 = 0;
i2.forEach((line) => {
  var badIfSee = {};
  var good = true;

  line.reverse().forEach((num) => {
    if (good && badIfSee[num]) {
      badLines.push(line);
      good = false;
    }
    i1.filter((x) => x[0] == num)
      .map((x) => x[1])
      .forEach((x) => (badIfSee[x] = true));
  });

  if (good) {
    idx = Math.floor(line.length / 2);
    star1 += parseInt(line[idx]);
  }
});

console.log("Star 1:", star1); // Expect: 4959

// Part 2
var fixedLines = badLines.map((line) => {
  var placed = {};
  return line.reduce((acc, num) => {
    var mustBefore = i1
      .filter((x) => x[0] == num)
      .map((x) => x[1])
      .filter((x) => placed[x]);
    var mustAfter = i1
      .filter((x) => x[1] == num)
      .map((x) => x[0])
      .filter((x) => placed[x]);

    var minIdx = acc.findLastIndex((x) => mustAfter.includes(x));
    var maxIdx = acc.findIndex((x) => mustBefore.includes(x));

    var pickedIdx = minIdx != -1 ? minIdx + 1 : maxIdx != -1 ? maxIdx : 0;

    placed[num] = true;
    acc.splice(pickedIdx, 0, num);
    return acc;
  }, []);
});
var star2 = fixedLines
  .map((line) => parseInt(line[Math.floor(line.length / 2)]))
  .reduce((a, x) => a + x, 0);
console.log("Star 2:", star2); // Expect: 4655
