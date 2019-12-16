import re
from collections import defaultdict

moons = []
for line in open('in').readlines():
  match = re.match('<x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)>', line)
  moons.append(([int(match.group(1)), int(match.group(2)), int(match.group(3))],[0,0,0]))

def gravity(m1, m2):
  if m1[0][0] > m2[0][0]:
    m1[1][0] -= 1
    m2[1][0] += 1
  if m1[0][1] > m2[0][1]:
    m1[1][1] -= 1
    m2[1][1] += 1
  if m1[0][2] > m2[0][2]:
    m1[1][2] -= 1
    m2[1][2] += 1
  if m1[0][0] < m2[0][0]:
    m1[1][0] += 1
    m2[1][0] -= 1
  if m1[0][1] < m2[0][1]:
    m1[1][1] += 1
    m2[1][1] -= 1
  if m1[0][2] < m2[0][2]:
    m1[1][2] += 1
    m2[1][2] -= 1

def simul(n):
  for i in range(n):
    for i in range(len(moons) - 1):
      for j in range(i+1, len(moons)):
        gravity(moons[i], moons[j]);
    for i in range(len(moons)):
      moons[i][0][0] += moons[i][1][0]
      moons[i][0][1] += moons[i][1][1]
      moons[i][0][2] += moons[i][1][2]

m = moons.copy()
simul(1000)
t = 0
for i in range(len(moons)):
  t += (abs(moons[i][0][0])+abs(moons[i][0][1])+abs(moons[i][0][2]))*(abs(moons[i][1][0])+abs(moons[i][1][1])+abs(moons[i][1][2]))
  
print("p1", t)

moons = m
start = m.copy()

def get_periods():
  period = defaultdict(int)
  for axis in range(3):
    moons_axis = [moon[0][axis] for moon in moons]
    vels_axis = [moon[1][axis] for moon in moons]
        
    while True:
      simul(1)
      period[axis] += 1

      sp = True
      for i in range(len(start)):
        if start[i][0][axis] != moons_axis[i] or start[i][1][axis] != vels_axis[i]:
          sp = False

      if sp: break
  return period
    
def lcm(a, b):
    import math as m
    return a * b // m.gcd(a, b)

period = get_periods()

print("p2", lcm(period[0], lcm(period[1], period[2])))

