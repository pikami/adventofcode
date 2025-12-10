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
