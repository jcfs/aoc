lastA = 512
lastB = 191
count = 0
s = 0

for i in range(0, 50000000):
  lastA = (lastA * 16807 % 2147483647) 

  if (lastA % 4 != 0):
    continue



  while(True):
    lastB = (lastB * 48271 % 2147483647) 
    if (lastB % 8 == 0):
      break

  s+=1
  if (s > 5000000):
    break

  if (lastA & 0xFFFF) == (lastB & 0xFFFF):
    print count
    count += 1

print count
