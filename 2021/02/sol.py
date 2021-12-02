line = [x.split() for x in open('in').readlines()]

# part1
x, y = 0, 0
for i, amt in line:
  x += int(amt) if 'forward' in i else 0
  y += int(amt) if 'down' in i else 0
  y -= int(amt) if 'up' in i else 0
    
print(x * y)

# part2
aim, x, y = 0, 0, 0
for i, amt in line:
  if 'forward' in i:
    x += int(amt)
    y += aim * int(amt)

  aim += int(amt) if 'down' in i else 0
  aim -= int(amt) if 'up' in i else 0
    
print(x * y)
