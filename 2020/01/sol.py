g = [int(x) for x in open('in', 'r').read().splitlines()]
print(next(x*y for x in g for y in g if x+y == 2020))
print(next(x*y*z for x in g for y in g for z in g if x+y+z == 2020))
