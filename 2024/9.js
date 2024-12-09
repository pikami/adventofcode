input = "";

var p1 = (input) => {
  expanded = input
    .split("")
    .map((x) => parseInt(x))
    .reduce((a, x, i) => {
      return [
        ...a,
        ...Array.from(Array(x).keys()).map(() =>
          i % 2 == 0 ? Math.round(i / 2) : -1
        ),
      ];
    }, []);

  (current = 0), (back = expanded.length - 1);

  while (current < back) {
    if (expanded[current] != -1) {
      current++;
      continue;
    }
    if (expanded[back] == -1) {
      back--;
      continue;
    }
    expanded[current] = expanded[back];
    expanded[back] = -1;
  }
  ans = expanded.reduce((a, x, i) => (x != -1 ? a + x * i : a), 0);
  console.log(`Star 1 answer is: ${ans}`); // Expect: 6395800119709
};

var p2 = (input) => {
  blocks = input.split("").map((x) => parseInt(x));
  newBlocks = blocks.map((x, i) =>
    i % 2 == 0 ? { fid: Math.round(i / 2), size: x } : { fid: -1, size: x }
  );

  var compactEmpty = () => {
    for (var i = 0; i < newBlocks.length - 1; i++) {
      if (newBlocks[i].fid == -1 && newBlocks[i + 1].fid == -1) {
        newBlocks[i].size += newBlocks[i + 1].size;
        newBlocks.splice(i + 1, 1);
      }
    }
  };

  for (i = blocks.length - 1; i >= 0; i--) {
    if (i % 2 != 0) {
      continue;
    }

    if (blocks[i] == 0) {
      continue;
    }

    newLoc = newBlocks.findIndex((x) => x.fid == -1 && x.size >= blocks[i]);
    if (newLoc == -1) {
      continue;
    }

    fileId = Math.round(i / 2);
    oldLoc = newBlocks.findIndex((x) => x.fid == fileId);

    if (oldLoc < newLoc) {
      continue;
    }

    newBlocks[oldLoc].fid = -1;

    if (newBlocks[newLoc].size == blocks[i]) {
      newBlocks[newLoc].fid = fileId;
      continue;
    }

    blockToInsert = { fid: fileId, size: blocks[i] };
    newBlocks.splice(newLoc, 0, blockToInsert);
    newBlocks[newLoc + 1].size -= blocks[i];

    compactEmpty();
  }

  expanded = newBlocks.reduce((a, x) => {
    return [...a, ...Array.from(Array(x.size).keys()).map(() => x.fid)];
  }, []);

  ans = expanded.reduce((a, x, i) => (x != -1 ? a + x * i : a), 0);
  console.log(`Star 2 answer is: ${ans}`); // Expect: 6418529470362
};

p1(input);
p2(input);
