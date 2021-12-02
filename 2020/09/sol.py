n = [int(x) for x in open('in').readlines()]

p1 = 0
for x in range(25, len(n)):
	f = False
	for i in range(x - 26, x - 1):
		for y in range(x - 25, x):
			if n[i] + n[y] == n[x]:
				f = True
	if not f:
		print(n[x])
		p1 = n[x]
		break	


for window in range(25, len(n)):
	for i in range(len(n)-window):
		r = n[window:window+i]
		if sum(r) == p1:
			print(min(r)+max(r))
			break
