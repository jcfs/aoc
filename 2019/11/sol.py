output = []
input = []

def parse_opcode(line, pc, opc, base):
    c = str(line[pc]).rjust(5, '0')
    op = opc[int(c[-2:])]

    r = {'line': line, 'pc': pc}

    if c.endswith('9'):
      r["base"] = base

    for i in range(1, op[1]):
      if c[3 - i] == '1':
        r[f"arg{i}"] = line[pc + i]
      elif c[3 - i] == '2':
        r[f"arg{i}"] = line[base + line[pc + i]]
      elif c[3 - i] == '0':
        r[f"arg{i}"] = line[line[pc + i]]

    r["b1"] = [base if c[i] == '2' else 0 for i in range(5)]
    
    return (op[0], r)

def sum(line, pc, arg1, arg2, b1):
    line[b1[0] + line[pc + 3]] = arg1 + arg2;
    return pc + 4

def mul(line, pc, arg1, arg2, b1):
    line[b1[0] + line[pc + 3]] = arg1 * arg2;
    return pc + 4

def read(line, pc, arg1, b1):
    line[b1[2] + line[pc+1]] = input.pop(0)
    return pc + 2

def write(line, pc, arg1, b1):
    output.append(arg1)
    return pc + 2

def jit(line, pc, arg1, arg2, b1):
    return arg2 if arg1 != 0 else pc + 3

def jif(line, pc, arg1, arg2, b1):
    return arg2 if arg1 == 0 else pc + 3

def lt(line, pc, arg1, arg2, b1):
    line[b1[0] + line[pc+3]] = 1 if arg1 < arg2 else 0
    return pc + 4

def eq(line, pc, arg1, arg2, b1):
    line[b1[0] + line[pc+3]] = 1 if arg1 == arg2 else 0
    return pc + 4

def rebase(line, pc, base, arg1, b1):
    return pc + 2, base + arg1

opcodes = {
        1: (sum, 3),
        2: (mul, 3),
        3: (read, 2),
        4: (write, 2),
        5: (jit, 3),
        6: (jif, 3),
        7: (lt, 3),
        8: (eq, 3),
        9: (rebase, 2)
}

def process(line, pc, base):
    while True:
        tp = parse_opcode(line, pc, opcodes, base)
        r = tp[0](**tp[1])
        
        ci = line[pc]

        if type(r) == tuple:
          pc, base = r
        else:
          pc = r

        if str(ci)[-1] == '4' and len(output) == 2:
          return pc, base

        if line[pc] == 99:
            return None, None

line = [int(x) for x in open('in').readline().strip().split(",")] + [0]*1500

blacks = set()
whites = set()

def move(current, turn):
  p, dir = current

  if dir == '^' and turn == 0:
    return ((p[0]-1, p[1]), '<')
  if dir == '^' and turn == 1:
    return ((p[0]+1, p[1]), '>')
  if dir == '<' and turn == 0:
    return ((p[0], p[1]-1), 'v')
  if dir == '<' and turn == 1:
    return ((p[0], p[1]+1), '^')
  if dir == 'v' and turn == 0:
    return ((p[0]+1, p[1]), '>')
  if dir == 'v' and turn == 1:
    return ((p[0]-1, p[1]), '<')
  if dir == '>' and turn == 0:
    return ((p[0], p[1]+1), '^')
  if dir == '>' and turn == 1:
    return ((p[0], p[1]-1), 'v')

pc, base = 0, 0
input.append(0)
pos = ((0,0), '^')

while True:
  pc, base = process(line, pc, base)
  if pc == None:
    break
  color = output.pop(0)
  turn = output.pop(0)

  if color == 0:
    blacks.add(pos[0])
    whites.discard(pos[0])
  else:
    whites.add(pos[0])
    blacks.discard(pos[0])

  pos = move(pos, turn)
 

  if pos[0] in whites:
    input.append(1)
  else:
    input.append(0)


print("p1", len(whites)+len(blacks))

line = [int(x) for x in open('in').readline().strip().split(",")] + [0]*1500

blacks = set()
whites = set()
pc, base = 0, 0
input = [1]
pos = ((0,0), '^')

while True:
  pc, base = process(line, pc, base)
  if pc == None:
    break
  color = output.pop(0)
  turn = output.pop(0)

  if color == 0:
    blacks.add(pos[0])
    whites.discard(pos[0])
  else:
    whites.add(pos[0])
    blacks.discard(pos[0])

  pos = move(pos, turn)
  if pos[0] in whites:
    input.append(1)
  else:
    input.append(0)

min_x = min(min([x[0] for x in blacks]), min([x[0] for x in whites]))
max_x = max(max([x[0] for x in blacks]), max([x[0] for x in whites]))

min_y = min(min([x[1] for x in blacks]), min([x[1] for x in whites]))
max_y = max(max([x[1] for x in blacks]), max([x[1] for x in whites]))

for x in range(min_x, max_x + 1):
  for y in range(min_y, max_y + 1):
    p = '#' if (x, y) in whites else " "
    print(p, end="")
  print()

