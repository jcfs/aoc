def parse_opcode(line, pc, opc):
    c = str(line[pc]).rjust(5, '0')
    op = opc[int(c[-2:])]

    r = {'line': line, 'pc': pc}
    for i in range(1, op[1]):
        r[f"arg{i}"] = line[pc + i] if c[3 - i] == '1' else line[line[pc + i]]

    return (op[0], r)

def sum(line, pc, arg1, arg2):
    line[line[pc + 3]] = arg1 + arg2;
    return pc + 4

def mul(line, pc, arg1, arg2):
    line[line[pc + 3]] = arg1 * arg2;
    return pc + 4

def read(line, pc):
    line[line[pc+1]] = int(input())
    return pc + 2

def write(line, pc, arg1):
    print("output: ", arg1)
    return pc + 2

def jit(line, pc, arg1, arg2):
    return arg2 if arg1 != 0 else pc + 3

def jif(line, pc, arg1, arg2):
    return arg2 if arg1 == 0 else pc + 3

def lt(line, pc, arg1, arg2):
    line[line[pc+3]] = 1 if arg1 < arg2 else 0
    return pc + 4

def eq(line, pc, arg1, arg2):
    line[line[pc+3]] = 1 if arg1 == arg2 else 0
    return pc + 4

opcodes = {
        1: (sum, 3),
        2: (mul, 3),
        3: (read, 1),
        4: (write, 2),
        5: (jit, 3),
        6: (jif, 3),
        7: (lt, 3),
        8: (eq, 3)
}

def process(line):
    pc = 0
    while True:
        tp = parse_opcode(line, pc, opcodes)
        pc = tp[0](**tp[1])
        if line[pc] == 99:
            break

line = [int(x) for x in open('in').readline().strip().split(",")]
process(line)




