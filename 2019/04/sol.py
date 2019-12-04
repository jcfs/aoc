def has_f_digits(s, f):
  total = {}
  for c in s:
    if f(s.count(c)):
      return True
  return False

def is_increasing(s):
  return s == ''.join(sorted(s))

c_1 = 0;
c_2 = 0;

for i in range(245318, 765747):
  if is_increasing(str(i)):
    if has_f_digits(str(i), lambda x: x >= 2):
      c_1 += 1
    if has_f_digits(str(i), lambda x: x == 2):
      c_2 += 1

print("p1", c_1)
print("p2", c_2)
  
