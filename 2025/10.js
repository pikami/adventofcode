input = ``

cases = input.split('\n').map(line => {
  pts = line.split(' ')
  wanted = pts.shift().replaceAll(/[\[\]]/g, '').replaceAll('.', '0').replaceAll('#', '1').split('').map(Number)
  joltage = pts.pop().replaceAll(/[\{\}]/g, '').split(',').map(Number)
  btns = pts.map(btn => btn.replaceAll(/[\(\)]/g, '').split(',').map(Number))
  return { wanted, joltage, btns }
})

bfs_lights = (c) => {
  wanted_key = c.wanted.join(';')
  init = c.wanted.map((_) => 0);
  q = [{ state: init, path: [] }];
  seen = new Set();
  while (q.length > 0) {
    s = q.shift();

    key = s.state.join(';');
    if (seen.has(key)) {
      continue;
    }
    if (key == wanted_key) {
      return s.path
    }
    seen.add(key);

    c.btns.forEach((btn, i) => {
      nstate = s.state.slice();
      btn.forEach((i) => {
        nstate[i] = nstate[i] === 0 ? 1 : 0;
      });
      npath = s.path.slice();
      npath.push(i);
      q.push({ state: nstate, path: npath });
    });
  }
};

lights_paths = cases.map((c) => bfs_lights(c));
console.log(lights_paths.reduce((a, x) => a + x.length, 0));

var glpk_lib = await import('https://jvail.github.io/glpk.js/dist/index.js')
var glpk = await glpk_lib.default()

var total_presses = 0
for (var the_case of cases) {
  var lp = {
    name: 'LP',
    objective: {
      direction: glpk.GLP_MIN,
      name: 'presses',
      vars: the_case.btns.map((_, i) => ({ name: `x${i}`, coef: 1 }))
    },
    subjectTo: the_case.joltage.map((j, i) => ({
      name: `c${i}`,
      vars: the_case.btns
        .map((btn, btn_i) => ({ btn_i, btn }))
        .filter(({ btn, btn_i }) => btn.includes(i))
        .map(({ btn_i }) => ({ name: `x${btn_i}`, coef: 1 })),
      bnds: { type:glpk.GLP_FX, lb:j, ub:j }
    })),
    bounds: the_case.btns.map((_, i) => ({ name: `x${i}`, type: glpk.GLP_LO, lb: 0 })),
    generals: the_case.btns.map((_, i) => `x${i}`)
  }

  var res = await glpk.solve(lp, { msglev: glpk.GLP_MSG_OFF })

  total_presses += Object.values(res.result.vars).reduce((a, x) => a + x, 0)
}

console.log(total_presses)
