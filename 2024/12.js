var input = ``

var map = input.split("\n").map((x) => x.split("").map((y) => y));
var regions = [];
var regionMap = [];

for (var y = 0; y < map.length; y++) {
    regionMap.push([]);
}

for (var y = 0; y < map.length; y++) {
    for (var x = 0; x < map[0].length; x++) {
        // Try to join a region or create own
        if (y - 1 >= 0 && map[y - 1][x] === map[y][x]) {
            regionMap[y][x] = regionMap[y - 1][x];
        }
        if (x - 1 >= 0 && map[y][x - 1] === map[y][x]) {
            regionMap[y][x] = regionMap[y][x - 1];
        }
        if (regionMap[y][x] === undefined) {
            regionMap[y][x] = regions.length;
            regions.push({
                value: map[y][x],
                area: 0,
                perimeter: 0,
                sides: 0,
                active: true,
            })
        }

        // Check if we can combine surrounding regions
        if (y - 1 >= 0 && map[y - 1][x] === map[y][x] && regionMap[y - 1][x] !== regionMap[y][x]) {
            var oldRegionId = regionMap[y][x];
            regions[regionMap[y][x]].active = false;
            var regionA = regions[regionMap[y - 1][x]];
            var regionB = regions[regionMap[y][x]];
            regionA.area += regionB.area;
            regionA.perimeter += regionB.perimeter;
            regionA.sides += regionB.sides;
            for (var i = 0; i < regionMap.length; i++) {
                for (var j = 0; j < regionMap[0].length; j++) {
                    if (regionMap[i][j] === oldRegionId) {
                        regionMap[i][j] = regionMap[y - 1][x];
                    }
                }
            }
        }

        // Calculate fences
        if (y - 1 < 0 || map[y - 1][x] !== map[y][x]) {
            regions[regionMap[y][x]].perimeter++;
        }
        if (x - 1 < 0 || map[y][x - 1] !== map[y][x]) {
            regions[regionMap[y][x]].perimeter++;
        }
        if (y + 1 >= map.length || map[y + 1][x] !== map[y][x]) {
            regions[regionMap[y][x]].perimeter++;
        }
        if (x + 1 >= map[0].length || map[y][x + 1] !== map[y][x]) {
            regions[regionMap[y][x]].perimeter++;
        }

        // Update region
        regions[regionMap[y][x]].area++;

        // Count corners
        var topMatches = y - 1 >= 0 && map[y - 1][x] === map[y][x];
        var leftMatches = x - 1 >= 0 && map[y][x - 1] === map[y][x];
        var rightMatches = x + 1 < map[0].length && map[y][x + 1] === map[y][x];
        var bottomMatches = y + 1 < map.length && map[y + 1][x] === map[y][x];
        var topLeftMatches = y - 1 >= 0 && x - 1 >= 0 && map[y - 1][x - 1] === map[y][x];
        var topRightMatches = y - 1 >= 0 && x + 1 < map[0].length && map[y - 1][x + 1] === map[y][x];
        var bottomLeftMatches = y + 1 < map.length && x - 1 >= 0 && map[y + 1][x - 1] === map[y][x];
        var bottomRightMatches = y + 1 < map.length && x + 1 < map[0].length && map[y + 1][x + 1] === map[y][x];

        if (!topMatches && !leftMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (!topMatches && !rightMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (!bottomMatches && !leftMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (!bottomMatches && !rightMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (topMatches && leftMatches && !topLeftMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (topMatches && rightMatches && !topRightMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (bottomMatches && leftMatches && !bottomLeftMatches) {
            regions[regionMap[y][x]].sides++;
        }
        if (bottomMatches && rightMatches && !bottomRightMatches) {
            regions[regionMap[y][x]].sides++;
        }
    }
}

// Calculate total price
var total = regions.filter(x => x.active).reduce((acc, region) => {
    return acc + region.area * region.perimeter;
}, 0);
console.log(`Star 1 answer is: ${total}`); // Expect: 1431316

var totalPart2 = regions.filter(x => x.active).reduce((acc, region) => {
    return acc + region.sides * region.area;
}, 0);
console.log(`Star 2 answer is: ${totalPart2}`); // Expect: 821428
