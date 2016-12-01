import sys
import re

h = {}
pos = {}

openfileobject = open('in', 'r')
for line in openfileobject:
    for rd, speed, time, rest in re.findall('(\w+) .* (\d+) .* (\d+) .* (\d+) seconds\.', line):
        h[rd] = (int(speed), int(time), int(rest))

md = 0
for rd in h.keys():
    md = max(int(int((2503/(h[rd][1]+h[rd][2]))+1)*h[rd][0]*h[rd][1]), md)

print md
