var input = ``;

var cases = input.split("\n\n").map((caseStr) => {
  var [buttonA, buttonB, prize] = caseStr.split("\n");
  var ax = parseInt(buttonA.split(", ")[0].split("+")[1]);
  var ay = parseInt(buttonA.split(", ")[1].split("+")[1]);
  var bx = parseInt(buttonB.split(", ")[0].split("+")[1]);
  var by = parseInt(buttonB.split(", ")[1].split("+")[1]);
  var px = parseInt(prize.split(", ")[0].split("=")[1]);
  var py = parseInt(prize.split(", ")[1].split("=")[1]);

  return {
    a: { x: ax, y: ay },
    b: { x: bx, y: by },
    p: { x: px, y: py },
  };
});

var solve = (c, p2) => {
  if (p2) {
    c.p.x += 10000000000000;
    c.p.y += 10000000000000;
  }

  var determinant = c.a.x * c.b.y - c.a.y * c.b.x;
  if (determinant === 0) {
    return 0;
  }

  var A = (c.b.y * c.p.x - c.b.x * c.p.y) / determinant;
  var B = (c.a.x * c.p.y - c.a.y * c.p.x) / determinant;

  if (A % 1 !== 0 || B % 1 !== 0) {
    return -1;
  }

  return A * 3 + B;
};

var p1 = cases
  .map((x) => solve(x, false))
  .filter((x) => x != -1)
  .reduce((a, b) => a + b, 0);
console.log(`Star 1 answer is: ${p1}`); // Expect: 32067

var p2 = cases
  .map((x) => solve(x, true))
  .filter((x) => x != -1)
  .reduce((a, b) => a + b, 0);
console.log(`Star 2 answer is: ${p2}`); // 92871736253789
