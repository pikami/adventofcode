var input = ``;
var mapSize = 71;
var wallsToPlace = 1024;
var start = [0, 0];
var end = [70, 70];
var bigNumber = 1000000;

var wallCoords = input
  .split("\n")
  .map((coord) => coord.split(",").map((x) => parseInt(x)));
var map = Array(mapSize)
  .fill()
  .map(() => Array(mapSize).fill("."));

var printMap = () => {
  for (let i = 0; i < mapSize; i++) {
    console.log(map[i].join(""));
  }
};

wallCoords.slice(0, wallsToPlace).forEach((coord) => {
  map[coord[1]][coord[0]] = "#";
});

printMap();

var bfs = () => {
  var directions = [
    [1, 0],
    [-1, 0],
    [0, 1],
    [0, -1],
  ];
  var queue = [[...start, 0]]; // x, y, steps
  var seen = new Set();
  seen.add(`${start[0]},${start[1]}`);

  while (queue.length > 0) {
    var [x, y, steps] = queue.shift();
    if (x === end[0] && y === end[1]) {
      return steps;
    }

    for (var [dx, dy] of directions) {
      var nx = x + dx;
      var ny = y + dy;

      if (
        nx >= 0 &&
        ny >= 0 &&
        nx < map[0].length &&
        ny < map.length &&
        map[ny][nx] !== "#" &&
        !seen.has(`${nx},${ny}`)
      ) {
        queue.push([nx, ny, steps + 1]);
        seen.add(`${nx},${ny}`);
      }
    }
  }

  return -1;
};

console.log(`Star 1 answer is: ${bfs()}`); // Expect: 320
