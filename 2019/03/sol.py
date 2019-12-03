from math import *

moves = {
  'R': lambda p: (p[0]+1, p[1]),
  'L': lambda p: (p[0]-1, p[1]),
  'U': lambda p: (p[0], p[1]+1),
  'D': lambda p: (p[0], p[1]-1),
}

with open('in') as f:
  w1 = f.readline().strip().split(',')
  w2 = f.readline().strip().split(',')

def distance(x,y):
  return sum(abs(a-b) for a,b in zip(x,y))

def get_track(w):
  track = {}
  steps = 0
  p = (0, 0)

  for x in w:
    sz = int(x[1:])
    dir = x[0]
    for i in range(sz):
      p = moves[dir](p)
      steps += 1
      if p not in track:
        track[p] = steps;
  return track

track1 = get_track(w1)
track2 = get_track(w2)

# get track intersections
inter = set([a for a in track1.keys()]) & set([a for a in track2.keys()])

min_s, min_d = 10000, 10000

for i in inter:
  if min_d > distance((0, 0), i):
    min_d = distance((0, 0), i)
  if min_s > track1[i] + track2[i]:
    min_s = track2[i] + track1[i]

print("p1", min_d)
print("p2", min_s)
