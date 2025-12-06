input = ``

equate = (eqs, ops) => eqs.reduce((a, eq, i) => {
  fn = ops[i] == "+" ? (a,b) => a+b : (a,b) => a*b;
  init = ops[i] == "+" ? 0 : 1;
  return a + eq.reduce(fn, init)
}, 0)

lines = input.split('\n')
ops = lines.pop().split(" ").filter(x => x!="")
eqs1 = lines.reduce((a,line) => {
  line.split(" ").filter(x => x!="").map(Number).forEach((x,i)=>a[i].push(x))
  return a;
}, Array(ops.length).fill(0).map(() => []))
console.log(equate(eqs1, ops))

eqs2 = Array(ops.length).fill(0).map(() => [])
col = 0
for(x=0;x<lines[0].length;x++){
  num = ""
  for(y=0;y<lines.length;y++){
    num+=lines[y][x]
  }
  num = num.replaceAll(" ", "")
  if (num.length <= 0) {
    col++;
    continue;
  }

  eqs2[col].push(parseInt(num))
}
console.log(equate(eqs2, ops))
