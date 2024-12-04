var input = "";

var star1 = Array.from(input.matchAll(/mul\(([0-9]+),([0-9]+)\)/g))
  .map((x) => parseInt(x[1]) * parseInt(x[2]))
  .reduce((a, x) => a + x, 0);
console.log(`Star 1 answer is: ${star1}`); // Expect: 187833789

var star2 = Array.from(
  input.matchAll(/(mul\(([0-9]+),([0-9]+)\))|(do\(\))|(don't\(\))/g)
)
  .map((x) => ({ mul: parseInt(x[2]) * parseInt(x[3]), f: x[0] }))
  .reduce(
    (ctx, x) => {
      if (x.f.includes("mul") && ctx.enableMul) {
        ctx.sum += x.mul;
      }
      if (x.f.includes("do(")) {
        ctx.enableMul = true;
      }
      if (x.f.includes("don't(")) {
        ctx.enableMul = false;
      }
      return ctx;
    },
    { enableMul: true, sum: 0 }
  ).sum;
console.log(`Star 2 answer is: ${star2}`); // Expect: 94455185
