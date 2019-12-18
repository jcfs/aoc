pattern = [0, 1, 0, -1]

def gen_pattern(i, size):
  result = []

  index = 0
  while len(result) <= size:
    for j in range(i):
      result.append(pattern[index % 4])
    index += 1

  result.pop(0)
  return result

s = open('in').read().strip()
inp = [int(x) for x in s]

def part1(arr):
  for i in range(100):
    n = []
    for j in range(1, len(arr) + 1):
      p = gen_pattern(j, len(arr))
      v = 0
      for k in range(len(arr)):
        v += (arr[k] * p[k])
      n.append(abs(v)%10)
    arr = n.copy()
  return arr


arr = part1(inp.copy())
print("p1", ''.join(str(x) for x in arr[0:8]))
t = inp * 10000
offset = int(s[0:7])

t = t[offset:]
for k in range(100):
  for i in range(len(t) - 2, -1, -1):
    t[i] += t[i + 1]
    t[i] %= 10

print("p2", ''.join(str(x) for x in t[0:8]))
