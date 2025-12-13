var input = ``

var parts = input.split('\n\n')

var cases = parts.pop().split('\n').map(c => {
  var parts = c.split(' ')
  return {
    grid: parts.shift().replaceAll(':', '').split('x').map(Number),
    counts: parts.map(Number)
  }
})

var presents = parts
  .map(p => p.split('\n').slice(1).map(x => Array.from(x)))
  .map(grid => ({
    grid,
    s: grid.flat().filter(x => x == '#').length
  }))

var test = (c) => {
  // Could even fit???
  var want = c.counts.reduce((a, x, i) => a + presents[i].s * x, 0)
  var have = c.grid[0] * c.grid[1]
  if (want > have) {
    return false
  }

  // EZ fit???
  var total_has = c.counts.reduce((a, x) => a + x, 0)
  var total_fit = Math.floor(c.grid[0] / 3) * Math.floor(c.grid[1] / 3)
  if (total_fit >= total_has) {
    return true
  }

  throw new Error("Unsupported input m8")
}

console.log(cases.filter(test).length)
