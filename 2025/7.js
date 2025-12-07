input = ``

map = input.split('\n')
maxX = map[0].length
maxY = map.length
paths = {}
splitsHit = 0

drip = (x,y) => {
    if (x >= maxX || y >= maxY) return 1;
    if (paths[`${x};${y}`] != undefined) return paths[`${x};${y}`];
    if (map[y][x] == '^') {
        splitsHit++;
        paths[`${x-1};${y}`] = drip(x-1,y)
        paths[`${x+1};${y}`] = drip(x+1,y)
        return paths[`${x-1};${y}`] + paths[`${x+1};${y}`]
    }
    paths[`${x};${y}`] = drip(x,y+1)
    return paths[`${x};${y}`]
}

startX = Array.from(map[0]).findIndex(x => x == 'S')
s2 = drip(startX, 0, 0)

console.log(splitsHit)
console.log(s2)
