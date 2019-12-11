from math import atan2
from time import sleep

m = open('in').read().splitlines()

asteroids = []
for y in range(len(m)):
  for x in range(len(m[0])):
    if m[y][x] == '#':
      asteroids.append((x, y)) 

def is_on(a, b, c):
    return (collinear(a, b, c)
            and (within(a[0], c[0], b[0]) if a[0] != b[0] else
                 within(a[1], c[1], b[1])))

def collinear(a, b, c):
    return (b[0] - a[0]) * (c[1] - a[1]) == (c[0] - a[0]) * (b[1] - a[1])

def within(p, q, r):
    return p <= q <= r or r <= q <= p

def get_visible(a):
   vis = []
   for b in asteroids:
    if b != a:
      h = False
      for c in asteroids:
        if c==a or c== b:
          continue
        if is_on(a, b, c):
          h = True
          break
      if not h:
        vis.append(b)
   return vis


max = 0
station = (0, 0)
for a in asteroids:
  t = len(get_visible(a))
  if (t > max):
    station = a
    max = t

print("p1", max)
a = station
v = [(atan2(b[0]-a[0], b[1]-a[1]), b) for b in get_visible(a)]
v.sort(reverse=True)
print("p2", v[199])
