i = [x.strip() for x in open('in').readlines()]

gamma, epsilon = '', ''
os, zs = 0, 0
for k in range(len(i[0])):
  for j in i:
    os += 1 if j[k] == '1' else 0
    zs += 1 if j[k] == '0' else 0
  gamma += '1' if os > zs else '0'
  epsilon += '0' if os > zs else '1'
  os, zs = 0,0

print(int(gamma,2) * int(epsilon,2))

x = i
# oxygen
while(len(x) > 1):
  for k in range(len(x[0])):
    for j in x:
      os += 1 if j[k] == '1' else 0
      zs += 1 if j[k] == '0' else 0

    v = '1' if os >= zs else '0'

    os, zs = 0, 0 
    t = x
    x = [y for y in t if y[k] == v]

    if len(x) == 1:
      break
 
h = i
# co2
while(len(h) > 1):
  for k in range(len(h[0])):
    for j in h:
      os += 1 if j[k] == '1' else 0
      zs += 1 if j[k] == '0' else 0

    v = '0' if os >= zs else '1'
    os, zs = 0, 0 
    t = h
    h = [y for y in t if y[k] == v]

    if len(h) == 1:
      break

print(int(x[0],2)*int(h[0],2))

