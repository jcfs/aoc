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

  def get_n(self, n):
    if len(self.output) < n:
      return None
    else:
      return [self.output.pop(0) for x in range(n)]

  def get_output(self):
    out = self.output
    self.output = []
    return out

  def run(self, i):
    if i is not None:
      self.input.extend(i)
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

vms = []
inputs = defaultdict(list)
for i in range(50):
  vms.append(IntCodeVm(line.copy()))
  vms[i].run([i])

def get_input(i):
  input = inputs[i]
  if len(input) > 0:
    return [input.pop(0) for x in range(len(input))]
  else:
    return [-1]

def set_output(o):
  i, x, y = o
  if i == 'NAT':
    inputs[i] = []

  inputs[i].append(x)
  inputs[i].append(y)

while True:
  idle = True
  for i in range(50):
    vms[i].run(get_input(i))
    outs = vms[i].get_n(3)
    if outs is not None:
      idle = False
      n, x, y = outs
      if n == 255:
        print(y)
        set_output(['NAT', x, y])
      else:
        set_output(outs)
  if idle:
    if len(inputs['NAT']) == 0:
      break
    print(inputs['NAT'])
    set_output([0, inputs['NAT'].pop(0), inputs['NAT'].pop(0)])
