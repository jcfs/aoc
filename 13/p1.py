import sys
import re
from itertools import permutations
from collections import defaultdict

def calc_h(perm):
  calc = 0
  l = len(perm);
  for i, part in enumerate(perm):
    j = (i+1) % (len(perm))
    calc += int(h[part][perm[j]])
    calc += int(h[perm[j]][part])
  return calc

h = defaultdict(dict)
with open('in2') as openfileobject:
  for line in openfileobject:
    for s, sig, happy, d in re.findall('(\w+) would (\w+) (\d+) happiness units by sitting next to (\w+)\.', line):
      h[s][d] = int(happy) * (1 if sig == 'gain' else -1)

c = 0
for x in permutations(h.keys()):
  c = max(calc_h(x), c)

print c
