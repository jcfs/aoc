import json
import sys

def getSum(js):
  sum = 0
  if isinstance(js, list):
    for value in js:
      if isinstance(value, int):
        sum += value
      else:
        sum += getSum(value)
    return sum
  elif isinstance(js, int):
    return js
  elif isinstance(js, basestring):
    return 0
  else:
    for key in js:
      sum +=getSum(js[key])
    return sum;

inp = sys.stdin.readline()
js = json.loads(inp)

sum = getSum(js)
print sum
