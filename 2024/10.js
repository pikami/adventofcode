input = ``;

var map = input.split("\n").map((x) => x.split("").map((y) => parseInt(y)));

var trailHeads = {};
var walkRecursive = function (x, y, path) {
  if (map[x][y] === 9) {
    var key = path[0].x + "-" + path[0].y;
    if (!trailHeads[key]) {
      trailHeads[key] = { ends: {} };
    }
    if (!trailHeads[key].ends[`${x}-${y}`]) {
      trailHeads[key].ends[`${x}-${y}`] = 0;
    }
    trailHeads[key].ends[`${x}-${y}`]++;
    return;
  }

  var newPath = [...path, { x, y }];
  if (x + 1 < map.length && map[x + 1][y] == map[x][y] + 1)
    walkRecursive(x + 1, y, newPath);
  if (x - 1 >= 0 && map[x - 1][y] == map[x][y] + 1)
    walkRecursive(x - 1, y, newPath);
  if (y + 1 < map[x].length && map[x][y + 1] == map[x][y] + 1)
    walkRecursive(x, y + 1, newPath);
  if (y - 1 >= 0 && map[x][y - 1] == map[x][y] + 1)
    walkRecursive(x, y - 1, newPath);
};

for (var i = 0; i < map.length; i++) {
  for (var j = 0; j < map[0].length; j++) {
    if (map[i][j] === 0) {
      walkRecursive(i, j, []);
    }
  }
}

var scoreSum = Object.keys(trailHeads)
  .map((key) => Object.keys(trailHeads[key].ends).length)
  .reduce((a, b) => a + b, 0);
console.log(scoreSum); // Expect: 510

var ratingSum = Object.keys(trailHeads)
  .map((key) => Object.values(trailHeads[key].ends))
  .map((ends) => ends.reduce((a, b) => a + b, 0))
  .reduce((a, b) => a + b, 0);
console.log(ratingSum); // Expect: 1058
