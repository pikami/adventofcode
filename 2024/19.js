var input = ``;

var available = input.split('\n')[0].split(', ');
var targets = input.split('\n').slice(2);

var canBeMade = (available, target) => {
    var canMake = Array(target.length + 1).fill(false);
    canMake[0] = true;

    for (var i = 1; i <= target.length; i++) {
        for (var j = 0; j < available.length; j++) {
            var color = available[j];
            if (color.length <= i && target.substring(i - color.length, i) === color) {
                canMake[i] = canMake[i - color.length] || canMake[i];
            }
        }
    }

    return canMake[target.length];
}

var possibleTargets = targets.filter((target) => canBeMade(available, target));

console.log(`Star 1 answer is: ${possibleTargets.length}`); // Expect: 240
