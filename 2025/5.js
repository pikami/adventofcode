input = ``

ranges = input
  .split('\n\n')[0].split('\n')
  .map(x => x.split('-').map(Number))
  .map(([start,end]) => ({start,end}))
  .sort((a, b) => a.start - b.start)
  .reduce((merged, x) => {
    const last = merged[merged.length - 1];
    if (!last || x.start > last.end) {
      merged.push({ ...x });
    } else {
      last.end = Math.max(last.end, x.end);
    }
    return merged;
  }, [])
  
ids = input.split('\n\n')[1].split('\n').map(Number)
fresh = ids.filter(x => ranges.some(r => r.start <= x && r.end >= x)).length
console.log(fresh)

allFresh = ranges.map(x => x.end - x.start + 1).reduce((a, x) => a+x, 0)
console.log(allFresh)
