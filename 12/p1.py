import json
import sys

def getSum(js):
  if isinstance(js, list):
    return sum([getSum(value) for value in js])
  elif isinstance(js, int):
    return js
  elif isinstance(js, basestring):
    return 0
  else:
    return sum([getSum(js[key]) for key in js])

inp = sys.stdin.readline()
js = json.loads(inp)

sum = getSum(js)
print sum
