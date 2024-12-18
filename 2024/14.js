var input = ``;

var maxX = 101, maxY = 103;
var ticsToSimulate = 100;

var guards = input.split("\n").map((line) => {
  var p = line.split(" ")[0].split("=")[1].split(",").map((x) => parseInt(x));
  var v = line.split(" ")[1].split("=")[1].split(",").map((x) => parseInt(x));
  return {
    p: { x: p[0], y: p[1] },
    v: { x: v[0], y: v[1] },
  };
});

var getQuadrant = (x, y) => {
    if (x == Math.floor(maxX / 2) || y == Math.floor(maxY / 2)) {
        return -1;
    }

    if (x < maxX / 2 && y < maxY / 2) {
        return 0;
    } else if (x >= maxX / 2 && y < maxY / 2) {
        return 1;
    } else if (x < maxX / 2 && y >= maxY / 2) {
        return 2;
    } else {
        return 3;
    }
}  

var guardPositionsAfrerTics = (guards, tics) => {
  return guards.map((guard) => {
    var newPos = {
      x: (guard.p.x + guard.v.x * tics + maxX * 100) % maxX,
      y: (guard.p.y + guard.v.y * tics + maxY * 100) % maxY,
    };
    newPos.quadrant = getQuadrant(newPos.x, newPos.y);
    return newPos;
  });
}

var guardsAfterTics = guardPositionsAfrerTics(guards, ticsToSimulate);

var star1 = guardsAfterTics
    .filter((guard) => guard.quadrant !== -1)
    .reduce((acc, guard) => {
        acc[guard.quadrant] = (acc[guard.quadrant] || 0) + 1;
        return acc;
    }, [])
    .reduce((acc, x) => acc * x, 1);

console.log(`Star 1 answer is: ${star1}`); // Expect: 231019008
