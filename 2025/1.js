const input = ``;
input.split('\n')
  .map(x => x.replaceAll('L', '-').replaceAll('R', ''))
  .map(x => parseInt(x))
  .reduce((a, x) => {
    a.hits += Math.abs(Math.floor((a.pos+x)/100));
    a.pos = ((a.pos+x)%100);
    a.pos = a.pos >= 0 ? a.pos : a.pos+100;
    a.lands += a.pos == 0 ? 1 : 0;
    return a;
  }, ({pos: 50, lands: 0, hits: 0}));
