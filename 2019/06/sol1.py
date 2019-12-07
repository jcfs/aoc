from collections import defaultdict

a = defaultdict(list)
f = open('in').readlines()

def point_to(node, rr):
  for k in rr:
    if node in rr[k]:
      return 1 + point_to(k, rr)
  return 0

def count_orbits(rr):
  dir, indir = 0, 0
  for k in rr:
    # count direct orbits as the number of children
    dir += len(rr[k])
    # count indirect orbits as the planets that point to k 
    e = point_to(k, rr)
    indir += e - 1 if e > 0 else 0
  return dir, indir;

for x in f:
  s, p = x.strip().split(')')
  a[s].append(p)

  if p not in a:
    a[p] = []

print(sum(count_orbits(a)))
