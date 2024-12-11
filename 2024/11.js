var input = ``;
var nums = input.split(" ").map((x) => parseInt(x));

var lengthAfterBlinksRecursive = (stone, blinksLeft) => {
    if (blinksLeft == 0) {
        return 1;
    }

    if (stone == 0) {
        return lengthAfterBlinksRecursiveCached(1, blinksLeft - 1);
    }

    if (stone.toString().length % 2 == 0) {
        var str = stone.toString();
        var half = str.length / 2;
        var left = parseInt(str.substring(0, half));
        var right = parseInt(str.substring(half));
        return lengthAfterBlinksRecursiveCached(left, blinksLeft - 1) + lengthAfterBlinksRecursiveCached(right, blinksLeft - 1);
    }

    return lengthAfterBlinksRecursiveCached(stone * 2024, blinksLeft - 1);
}

var cache = {};
var lengthAfterBlinksRecursiveCached = (stone, blinksLeft) => {
    if (cache[`${stone}-${blinksLeft}`]) {
        return cache[`${stone}-${blinksLeft}`];
    }

    cache[`${stone}-${blinksLeft}`] = lengthAfterBlinksRecursive(stone, blinksLeft);
    return cache[`${stone}-${blinksLeft}`];
}

var lengthAfterBlinks = (stones, blinks) => {
    var total = 0;
    for (var i = 0; i < stones.length; i++) {
        total += lengthAfterBlinksRecursiveCached(stones[i], blinks);
    }
    return total;
}

console.log(`Star 1 answer is: ${lengthAfterBlinks(nums, 25)}`); // Expect: 202019
console.log(`Star 2 answer is: ${lengthAfterBlinks(nums, 75)}`); // Expect: 239321955280205
