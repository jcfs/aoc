p = [(l.split()[0], int(l.split()[1])) for l in open('in').readlines()]

def run(p, detect_loop = False):
	pc = 0
	acc = 0
	v = set()
	while pc not in v and pc < len(p):
		i, value = p[pc]
		if detect_loop:
			v.add(pc)
		pc += 1
		if i == 'jmp':
			pc += value - 1
		elif i == 'acc':
			acc += value
	return acc, pc == len(p)

print(run(p, True)[0])

swap = {'jmp': 'nop', 'nop': 'jmp', 'acc': 'acc' }
for i in range(len(p)):
	u, value = p[i]
	p[i] = (swap[u], value)
	acc, finished = run(p, True)
	if finished:
		print(acc)
		break
	p[i] = (u, value)
