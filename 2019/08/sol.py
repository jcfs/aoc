h, w = 6, 25

a = [int(x) for x in list(open('in').readline().strip())]
b = [2] * (h*w)

min_z = 10000

for i in range(int(len(a) / (h*w))):
    offset = i * h * w
    lb, hb = offset, h * w + offset

    zeros = a[lb:hb].count(0)
    ones = a[lb:hb].count(1)
    twos = a[lb:hb].count(2)

    if zeros < min_z:
       p1 = ones * twos
       min_z = zeros

    # for part2 lets run through them all
    for y in range(h * w):
        c = a[y + offset]
        b[y] = c if b[y] == 2 else b[y]

print("p1", p1)
print("p2", end = '')
for y in range(h * w):
    if y % w == 0:
        print("")
    print(b[y] if b[y] != 0 else ' ', end = '')


