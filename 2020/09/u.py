import itertools

def day09(inp):
    lines = [int(line) for line in open('in').readlines()]

    for i in range(25,len(lines)):
        n = lines[i]
        if not any(n == a + b for a, b in itertools.permutations(lines[i-25:i], 2)):
            print('p1:', n)
            invalid_num = n
            break
    
    for width in range(2,len(lines)):
        for i in range(len(lines)-width):
            s = lines[i:i+width]
            if sum(s) == invalid_num:
                print('p2:', min(s)+max(s))
                return

day09(open('in').readlines())
