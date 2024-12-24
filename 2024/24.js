var input = ``;

var inputBlocks = input.split("\n\n");
var gateToValue = inputBlocks[0]
  .split("\n")
  .map((x) => x.split(": "))
  .reduce((acc, x) => {
    acc[x[0]] = parseInt(x[1]);
    return acc;
  }, {});
var gates = inputBlocks[1]
  .split("\n")
  .map((x) => x.split(" "))
  .map((x) => ({
    i1: x[0],
    i2: x[2],
    out: x[4],
    oper: x[1],
  }));

var getValueRecursive = (gate) => {
  if (gate in gateToValue) {
    return gateToValue[gate];
  }

  var gateObj = gates.find((x) => x.out === gate);
  var i1 = getValueRecursive(gateObj.i1);
  var i2 = getValueRecursive(gateObj.i2);
  var value;
  switch (gateObj.oper) {
    case "AND":
      value = i1 & i2;
      break;
    case "OR":
      value = i1 | i2;
      break;
    case "XOR":
      value = i1 ^ i2;
      break;
    default:
      value = i1;
  }
  gateToValue[gate] = value;
  return value;
};

var gatesToCalculate = gates.filter((x) => x.out.startsWith("z"));
gatesToCalculate.forEach((x) => getValueRecursive(x.out));

var resultBinary = gatesToCalculate
  .sort((a, b) => a.out.localeCompare(b.out))
  .map((x) => gateToValue[x.out])
  .reverse()
  .join("");

var result = parseInt(resultBinary, 2);
console.log(`Star 1 answer is: ${result}`); // Expect: 57344080719736
