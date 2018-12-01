lastA = 512
lastB = 191
count = 0

for i in range(0, 40000000):
  lastA = lastA * 16807 % 2147483647
  lastB = lastB * 48271 % 2147483647
  if (lastA & 0xFFFF) == (lastB & 0xFFFF):
    print count
    count += 1

print count
