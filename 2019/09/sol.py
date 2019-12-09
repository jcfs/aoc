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
    line[b1[2] + line[pc+1]] = int(input())
    return pc + 2

def write(line, pc, arg1, b1):
    print(arg1)
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

def process(line, base):
    pc = 0
    while True:
        tp = parse_opcode(line, pc, opcodes, base)
        r = tp[0](**tp[1])
        
        if type(r) == tuple:
          pc, base = r
        else:
          pc = r

        if line[pc] == 99:
            break

line = [int(x) for x in open('in').readline().strip().split(",")] + [0] * 1000

process(line, 0)




