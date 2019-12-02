
opcodes = {
        1: lambda mem, x : mem[mem[x+1]] + mem[mem[x+2]],
        2: lambda mem, x : mem[mem[x+1]] * mem[mem[x+2]],
}

def process(l, n, v):
    i, l[1], l[2] = 0, n, v
    i = 0

    while l[i] in opcodes:
        l[l[i+3]] = opcodes[l[i]](l, i)
        i = i+4

    return l[0]


line = [int(x) for x in open('in').readline().strip().split(",")]

# part one
print("p1", process(line.copy(), 12, 2))

# part two
for i in range(100):
    for y in range(100):
        if process(line.copy(), i, y) == 19690720:
            print("p2", 100 * i + y)



