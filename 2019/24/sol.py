from collections import defaultdict

m = open('in').read().strip().split('\n')

H = len(m)
W = len(m[0].strip())

ma = defaultdict(int)
seen = set()

def mb(s):
  m1 = ""
  for i in range(H):
    for j in range(W):
      m1 += str(s[(j, i)])

  print(m1)
  m1 = m1.replace('\n', '').replace('.', '0').replace('#', '1')[::-1]
  return int(m1, 2)

for i in range(H):
  for j in range(W):
    if m[i][j] == '.':
      ma[(j, i)] = 0
    else:
      ma[(j, i)] = 1

def next_gen(s):
  ns = defaultdict(int)
  for y in range(H):
    for x in range(W):
      adj = s[(x, y-1)]+s[(x-1, y)]+s[(x+1, y)]+s[(x, y+1)]
      if s[(x,y)] == 1 and adj != 1:
        ns[(x,y)] = 0
      elif s[(x,y)] == 0 and (adj == 2 or adj == 1):
        ns[(x,y)] = 1
      else:
        ns[(x,y)] = s[(x,y)]
  return ns

def print_s(s):
  for y in range(H):
    for x in range(W):
      print('#' if s[(x, y)] == 1 else '.', end='')
    print()

while True:
  b = mb(ma)
  print_s(ma)
  if b in seen:
     print(b)
     break

  seen.add(b)

#print(ma)
  ma = next_gen(ma)
#print(ma)


