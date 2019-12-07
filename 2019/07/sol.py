from itertools import permutations

def parse_opcode(line, pc, opc, input, output):
    c = str(line[pc]).rjust(5, '0')
    op = opc[int(c[-2:])]

    r = {'line': line, 'pc': pc, 'ia': input, 'oa': output}
    for i in range(1, op[1]):
        r[f"arg{i}"] = line[pc + i] if c[3 - i] == '1' else line[line[pc + i]]

    return (op[0], r)

def sum(line, pc, arg1, arg2, ia, oa):
    line[line[pc + 3]] = arg1 + arg2;
    return pc + 4

def mul(line, pc, arg1, arg2, ia, oa):
    line[line[pc + 3]] = arg1 * arg2;
    return pc + 4

def read(line, pc, ia, oa):
    line[line[pc+1]] = ia.pop(0)
    return pc + 2

def write(line, pc, arg1, ia, oa):
    oa.append(arg1)
    return pc + 2

def jit(line, pc, arg1, arg2, ia, oa):
    return arg2 if arg1 != 0 else pc + 3

def jif(line, pc, arg1, arg2, ia, oa):
    return arg2 if arg1 == 0 else pc + 3

def lt(line, pc, arg1, arg2, ia, oa):
    line[line[pc+3]] = 1 if arg1 < arg2 else 0
    return pc + 4

def eq(line, pc, arg1, arg2, ia, oa):
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

def process(program):
    program["output"] = []
    pc = program["pc"]
    line = program["line"]

    while line[pc] != 99:
        tp = parse_opcode(**program)
        program["pc"] = tp[0](**tp[1])
        # we have some output lets return
        if len(program["output"]) > 0:
            return program

    program["output"].append(None)
    return program

def init_prog(line, pc, input, output):
    return {'line': line, 'pc': pc, 'input': input, 'output': output, 'opc': opcodes}

def solve_p1():
    p1 = 0
    for perm in permutations([0, 1, 2, 3, 4]):
        initial_in = 0
        for phase in perm:
            initial_in = process(init_prog(line.copy(), 0, [phase, initial_in], []))["output"][0]
        if initial_in > p1:
            p1 = initial_in

    return p1

def solve_p2():
    p2 = 0
    for perm in permutations([5, 6, 7, 8, 9]):
        initial_in, output = 0, 0

        programs = []
        for i in range(0, 5):
            programs.append(init_prog(line.copy(), 0, [perm[i]], []))

        while output is not None:
            for i in range(0, 5):
                programs[i]["input"].append(output)
                output = process(programs[i])["output"][0]
            if output != None:
                final_output = output
        if final_output > p2:
            p2 = final_output
    return p2

line = [int(x) for x in open('in').readline().strip().split(",")]

print("p1", solve_p1())
print("p2", solve_p2())




