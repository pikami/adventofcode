input = ``
target = 1000

pts = input.split('\n').map(x => x.split(',').map(Number))

getDst = (a, b) => Math.pow(a[0]-b[0], 2) + Math.pow(a[1]-b[1], 2) + Math.pow(a[2]-b[2], 2)
dst = {}
for (i = 0; i < pts.length; i++) {
  for (o = i + 1; o < pts.length; o++) {
    dst[`${i};${o}`] = getDst(pts[i], pts[o])
  }
}
dst = Object.entries(dst).sort((a,b) => a[1]-b[1])

circuits = []
place = (p) => {
  ids = p[0].split(';')
  c1 = circuits.find(s => s.has(ids[0]))
  c2 = circuits.find(s => s.has(ids[1]))
  if (c1 && c1 === c2) {
    return
  }

  if (c1 && c2) {
    c2.forEach(id => c1.add(id))
    circuits = circuits.filter(s => s !== c2)
    return
  }

  if (c1) {
    c1.add(ids[1])
    return
  }

  if (c2) {
    c2.add(ids[0])
    return
  }

  circuits.push(new Set(ids))
  return
}

for (i = 0; i < target; i++) {
  place(dst[i])
}

s1 = circuits.map(c => c.size).sort((a,b) => b-a).splice(0, 3).reduce((a,x) => a*x, 1)
console.log(s1)

for (i = target; i < dst.length; i++) {
  place(dst[i])
  if (circuits.length == 1 && circuits[0].size == pts.length) {
    lastConn = dst[i][0].split(';').map(Number)
    s2 = pts[lastConn[0]][0] * pts[lastConn[1]][0]
    console.log(s2)
    break
  }
}
