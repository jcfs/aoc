g = [int(x) for x in open('in').readlines()]

def sum_inc(arg):
  print(sum(n > p for p, n in zip(arg, arg[1:])))


# part 1
sum_inc(g)

# part 2
windows = [sum(g[i:i+3]) for i in range(len(g))]
sum_inc(windows)
