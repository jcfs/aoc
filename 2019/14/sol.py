import math
from collections import defaultdict

lines = open('in').read().strip().split("\n")

reactions = {}
excess = defaultdict(int)

for line in lines:
  i, o = line.split(" => ")
  i = i.split(', ')
  
  k = []
  for input in i:
    chem = input.split(" ")
    k.append((int(chem[0]), chem[1]))
  o = (o.split(" ")[0],o.split(" ")[1])
  reactions[o[1]] = (int(o[0]), k)

def collect(chem, amt):
  if chem == 'ORE':
    return amt

  e = min(amt, excess[chem])
  amt -= e
  excess[chem] -= e

  produced, inputs = reactions[chem]
  n = math.ceil(amt / produced)

  ore = 0

  for required, input in inputs:
    ore += collect(input, n * required)

  excess[chem] += n * produced - amt

  return ore

print("p1", collect('FUEL', 1))

low, high = 0, 1000000000

while low + 1 < high:
  mid = (low + high) // 2
  excess = defaultdict(int)
  ore = collect('FUEL', mid)
  if ore > 1000000000000:
    high = mid
  elif ore < 1000000000000:
    low = mid

print("p2", low)
