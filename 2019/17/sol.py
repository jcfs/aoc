import sys
from collections import defaultdict

class IntCodeVm:
  def __init__(self, code, pc = 0, input = []):
    self.code = code.copy()
    self.pc = pc
    self.base = 0
    self.input = input
    self.output = []

  def parse_opcode(self):
    c = str(self.code[self.pc]).rjust(5, '0')
    r = {}

    for i in range(1, 4):
      try:
        if c[3 - i] == '1':
          r[f"arg{i}"] = self.code[self.pc + i]
        elif c[3 - i] == '2':
          r[f"arg{i}"] = self.code[self.base + self.code[self.pc + i]]
        elif c[3 - i] == '0':
          r[f"arg{i}"] = self.code[self.code[self.pc + i]]
      except:
        pass

    r["b1"] = [self.base if c[i] == '2' else 0 for i in range(5)]
    
    return r

  def get_output(self):
    out = self.output
    self.output = []
    return out

  def run(self, i):
    self.input.append(i)
    while self.code[self.pc] != 99:
      tp = self.parse_opcode()
      opcode = self.code[self.pc] % 100

      b1, arg1, arg2 = tp["b1"], tp["arg1"], tp["arg2"] if "arg2" in tp else None

      if opcode == 1:
        self.code[b1[0] + self.code[self.pc + 3]] = arg1 + arg2;
        self.pc += 4
      if opcode == 2:
        self.code[b1[0] + self.code[self.pc + 3]] = arg1 * arg2;
        self.pc += 4
      if opcode == 3:
        if len(self.input) > 0:
          self.code[b1[2] + self.code[self.pc+1]] = self.input.pop(0)
          self.pc += 2
        else:
          return False
      if opcode == 4:
        self.output.append(arg1)
        self.pc += 2
      if opcode == 5:
        self.pc = arg2 if arg1 != 0 else self.pc + 3
      if opcode == 6:
        self.pc = arg2 if arg1 == 0 else self.pc + 3
      if opcode == 7:
        self.code[b1[0] + self.code[self.pc+3]] = 1 if arg1 < arg2 else 0
        self.pc += 4
      if opcode == 8:
        self.code[b1[0] + self.code[self.pc+3]] = 1 if arg1 == arg2 else 0
        self.pc += 4
      if opcode == 9:
        self.base += arg1
        self.pc += 2

    return True

line = [int(x) for x in open('in').readline().strip().split(",")] + [0] * 5048

vm = IntCodeVm(line)
print(vm.run(0))

p = set()
x, y = 0, 0
for i in vm.get_output():
  if chr(i) == '#':
    p.add((x,y))

  x+=1

  if i == 10:
    y+=1
    x=0
  print(chr(i), end='')

print(p)

c = 0
for r in p:
  if (r[0]+1, r[1]) in p and (r[0]-1, r[1]) in p and (r[0], r[1]+1) in p and (r[0], r[1]-1) in p:
    c += r[0]*r[1]

print(c)
