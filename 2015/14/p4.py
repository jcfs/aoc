import sys
import re

h = {}
pos = {}

def distance(time, speed, rest_time, moving_time):
    return (int(time/(rest_time+moving_time))+1)*(speed*moving_time)



openfileobject = open('in', 'r')
for line in openfileobject:
    for rd, speed, time, rest in re.findall('(\w+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds\.', line):
        h[rd] = (int(speed), int(time), int(rest), 0)

md = 0
for i in range(1, 2504):
    for rd in h.keys():
        speed, moving_time, resting_time, distance_r = h[rd]
        distance_r = distance(i, h[rd][0], h[rd][2], h[rd][1])
        h[rd] = (speed, moving_time, resting_time, distance_r)

print h
