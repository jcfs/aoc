import sys
import re

h = {}
pos = {}

openfileobject = open('in', 'r')
for line in openfileobject:
    for rd, speed, time, rest in re.findall('(\w+) .* (\d+) km/s for (\d+) .* (\d+) .*\.', line):
        h[rd] = (int(speed), int(time), int(rest))
        pos[rd] = (int(rest), int(time), 'moving', 0, 0)

md = 0
mp = 0
for i in range(1, 2504):
    for rd in pos.keys():
        r, t, status, d, p = pos[rd]
        if (status == 'moving'):
            d += h[rd][0]
            t -= 1
            if (t == 0):
                r = h[rd][2]
                status  = 'resting'
        elif (status == 'resting'):
            r -= 1
            if (r == 0):
                t = h[rd][1]
                status = 'moving'

        pos[rd] = (r, t, status, d, p)
        md = max(d, md)

    for rd in pos.keys():
        r, t, status, d, p = pos[rd];
        if (d == md):
            p += 1
            mp = max(p, mp)
        pos[rd] = (r, t, status, d, p)

print mp
