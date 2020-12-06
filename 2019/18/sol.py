
data = open('in2').read()
maze = data.split("\n")

s = ()
keys = set()

for y in range(len(maze)-1):
  for x in range(len(maze[0])):
    if maze[y][x] == '@':
      s = (x, y, set(), 0)
    if maze[y][x] >= 'a' and maze[y][x] <= 'z':
      keys.add(maze[y][x])

dirs = [(0,1),(0,-1),(1,0),(-1,0)]

def get_n(e):
  n = []
  x, y, k = e

  for d in dirs:
    nx = x + d[0]
    ny = y + d[1]
    ch = maze[ny][nx]

    if (ch >= 'A' and ch <= 'Z' and ch.lower() in k):
      n.append((nx, ny))
    elif ch == '.' or ch >= 'a' and ch <= 'z':
      n.append((nx, ny))

  return n

visited = set()
queue = []
queue.append(s)

while len(queue) > 0:
  x, y, k, d = queue.pop(0)
  key = (x, y, tuple(sorted(k)))

  if key in visited:
    continue

  visited.add(key)

  k = k.copy()
  if maze[y][x] >= 'a' and maze[y][x] <= 'z':
    k.add(maze[y][x])
    if (len(k) == len(keys)):
      print("done", d)
      break

  for n in get_n((x,y,k)):
    queue.append((n[0], n[1], k, d+1))


