input = ``

pts = input.split('\n').map(x => x.split(',').map(Number))

c_rec = (p1, p2) => {
  maxX = Math.max(p1[0], p2[0])
  minX = Math.min(p1[0], p2[0])
  maxY = Math.max(p1[1], p2[1])
  minY = Math.min(p1[1], p2[1])
  s = (maxX-minX+1) * (maxY-minY+1)
  return { maxX, minX, maxY, minY, s }
}

recs = []
for (i = 0; i < pts.length; i++) {
  for (o = i + 1; o < pts.length; o++) {
    recs.push(c_rec(pts[i], pts[o]))
  }
}
maxS =recs.sort((a,b) => b.s-a.s)[0]
console.log(maxS.s)

lines = pts.map((x,i) => {
  if (i >= pts.length-1) {
    return c_rec(pts[i], pts[0])
  }
  return c_rec(pts[i], pts[i+1])
})

overlap = (r1, r2) => {
  return r1.minX < r2.maxX && r1.maxX > r2.minX && r1.minY < r2.maxY && r1.maxY > r2.minY
}

maxNoOverlap = recs.filter(rec => !lines.some(line => overlap(rec, line))).sort((a,b) => b.s-a.s)[0]
console.log(maxNoOverlap.s)
