print(sum(len(set.intersection(*map(set,g.split())))for g in open('i').read().split('\n\n')))
