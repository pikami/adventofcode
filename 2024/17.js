var input = `Register A: 59590048
Register B: 0
Register C: 0

Program: 2,4,1,5,7,5,0,3,1,6,4,3,5,5,3,0`;

var registers = input.split('\n\n')[0]
    .split('\n')
    .map(x => x.replaceAll('Register ', '').split(': '))
    .reduce((acc, x) => {
        acc[x[0]] = parseInt(x[1]);
        return acc;
    }, {});

var program = input.split('\n\n')[1].split(': ')[1].split(',').map(x => parseInt(x));

var run = (registers, program, expectedOutput) => {
    var ip = 0;
    var outputBuffer = [];

    var operandToCombo = (operand) => {
        if (operand === 4) return registers['A'];
        if (operand === 5) return registers['B'];
        if (operand === 6) return registers['C'];
        return operand;
    }

    var opcodeToFunc = {
        0: (operand) => registers['A'] = Math.floor(registers['A'] / (Math.pow(2, operandToCombo(operand)))),
        1: (operand) => registers['B'] = registers['B'] ^ operand,
        2: (operand) => registers['B'] = operandToCombo(operand) % 8,
        3: (operand) => registers['A'] != 0 ? ip = operand - 2 : null,
        4: (operand) => registers['B'] = registers['B'] ^ registers['C'],
        5: (operand) => outputBuffer.push(operandToCombo(operand) % 8),
        6: (operand) => registers['B'] = Math.floor(registers['A'] / (Math.pow(2, operandToCombo(operand)))),
        7: (operand) => registers['C'] = Math.floor(registers['A'] / (Math.pow(2, operandToCombo(operand)))),
    };

    while (ip < program.length) {
        var opcode = program[ip];
        var operand = program[ip + 1];
        opcodeToFunc[opcode](operand);
        ip += 2;
    }

    return {
        registers,
        program,
        ip,
        outputBuffer,
    }
}

// If register C contains 9, the program 2,6 would set register B to 1.
var actual1 = run({ A: 0, B: 0, C: 9 }, [2, 6]);
if (actual1.registers.B === 1) console.log('Test 1 passed');
else console.log('Test 1 failed');

// If register A contains 10, the program 5,0,5,1,5,4 would output 0,1,2.
var actual2 = run({ A: 10, B: 0, C: 0 }, [5, 0, 5, 1, 5, 4]);
if (actual2.outputBuffer.join(',') === '0,1,2') console.log('Test 2 passed');
else console.log('Test 2 failed');

// If register A contains 2024, the program 0,1,5,4,3,0 would output 4,2,5,6,7,7,7,7,3,1,0 and leave 0 in register A.
var actual3 = run({ A: 2024, B: 0, C: 0 }, [0, 1, 5, 4, 3, 0]);
if (actual3.outputBuffer.join(',') === '4,2,5,6,7,7,7,7,3,1,0' && actual3.registers.A === 0) console.log('Test 3 passed');
else console.log('Test 3 failed');

// If register B contains 29, the program 1,7 would set register B to 26.
var actual4 = run({ A: 0, B: 29, C: 0 }, [1, 7]);
if (actual4.registers.B === 26) console.log('Test 4 passed');
else console.log('Test 4 failed');

// If register B contains 2024 and register C contains 43690, the program 4,0 would set register B to 44354.
var actual5 = run({ A: 0, B: 2024, C: 43690 }, [4, 0]);
if (actual5.registers.B === 44354) console.log('Test 5 passed');
else console.log('Test 5 failed');

// Run actual:
var actual = run(registers, program);
var star1 = actual.outputBuffer.join(',');
console.log(`Star 1 answer is: ${star1}`); // Expect: 6,5,7,4,5,7,3,1,0
