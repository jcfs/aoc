import json
import sys

def getSum(js):
  if isinstance(js, list):
    return sum([getSum(key) for key in js])
  elif isinstance(js, int):
    return js
  elif isinstance(js, basestring):
    return 0
  else:
    return sum([getSum(js[key]) for key in js if not 'red' in js.values()])

inp = sys.stdin.readline()
js = json.loads(inp)

print getSum(js)
