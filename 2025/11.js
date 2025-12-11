const input = ``

const nodes = input.split('\n')
  .map(x => x.replaceAll(':', '').split(' '))
  .reduce((a, x) => {a[x.shift()] = x; return a;}, {})

const dfs = ({ seek, cur, memo, visiting }) => {
  if (cur == seek) {
    return 1
  }

  if (nodes[cur] == undefined) {
    return 0
  }

  if (visiting.has(cur)) {
    return 0
  }

  if (memo[cur] != undefined) {
    return memo[cur]
  }

  visiting.add(cur);
  let c = 0
  for (let next of nodes[cur]) {
    c += dfs({ cur: next, seek, memo, visiting })
  }
  visiting.delete(cur);

  memo[cur] = c

  return c
}

const s1 = dfs({ cur: "you", seek: "out", memo: {}, visiting: new Set() })
console.log(s1)

const svr_fft = dfs({ cur: "svr", seek: "fft", memo: {}, visiting: new Set() })
const fft_dac = dfs({ cur: "fft", seek: "dac", memo: {}, visiting: new Set() })
const dac_out = dfs({ cur: "dac", seek: "out", memo: {}, visiting: new Set() })

const svr_dac = dfs({ cur: "svr", seek: "dac", memo: {}, visiting: new Set() })
const dac_fft = dfs({ cur: "dac", seek: "fft", memo: {}, visiting: new Set() })
const fft_out = dfs({ cur: "fft", seek: "out", memo: {}, visiting: new Set() })

const s2 = svr_fft * fft_dac * dac_out + svr_dac * dac_fft * fft_out;
console.log(s2)
