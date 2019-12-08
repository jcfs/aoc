import numpy

size = 6 * 25

a = [int(x) for x in list(open('in').readline().strip())]
b = [2] * size

min_z = 10000

for i in range(len(a) // size):
    offset = i * size
    lb, hb = offset, size + offset

    zeros = a[lb:hb].count(0)
    ones = a[lb:hb].count(1)
    twos = a[lb:hb].count(2)

    if zeros < min_z:
       p1 = ones * twos
       min_z = zeros

    # for part2 lets run through them all
    b = [a[y + offset] if b[y] == 2 else b[y] for y in range(size)]

print("p1", p1)
print("p2")
for i in numpy.array_split(numpy.array(b), 6):
    print("".join(map(str, numpy.where(i == 0, ' ', i))).replace("1", "#"))

