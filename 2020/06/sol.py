x = [(len(i.splitlines()), [(x, i.count(x)) for x in set(i.replace('\n',''))]) for i in open('in', 'r').read().split('\n\n')]
print(sum(len(k[1]) for k in x))
print(sum(1 if (i[1] >= k[0]) else 0 for k in x for i in k[1]))
