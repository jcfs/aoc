import sys
import re
from itertools import combinations
from collections import defaultdict

def valid_table(t1):
  for i in t1:
    s = set(actorsCar[i])
    for j in t1:
      if j != i:
        t = set(actorsDis[j])
        if (len(t & s) != 0):
          return False
  return True

def valid_configuration(t1, t2, t3):
  return valid_table(t1) and valid_table(t2) and valid_table(t3)

actorsCar = defaultdict(dict)
actorsDis = defaultdict(dict)

with open('in') as openfileobject:
  for line in openfileobject:
    for actor, action, caracteristic in re.findall('(\w+) ([\w\ ]+) (\w+)$', line):
      if action == 'is':
        if actorsCar[actor] == {}:
          actorsCar[actor] = set([caracteristic])
        else:
          actorsCar[actor] = actorsCar[actor] | set([caracteristic])
      else:
        if actorsDis[actor] == {}:
          actorsDis[actor] = set([caracteristic])
        else:
          actorsDis[actor] = actorsDis[actor] | set([caracteristic])

actorsCar['Frank'] = actorsCar['Frank'] | set(['50'])
actorsCar['James'] = actorsCar['James'] | set(['50'])

confs = []
actors = set(actorsCar.keys())|set(actorsDis.keys())

for i in combinations(actors, 4):
  table1 = frozenset(i)
  for j in combinations(actors-table1, 4):
    table2 = frozenset(j)
    table3 = frozenset(actors - table2 - table1)
    if (valid_configuration(table1, table2, table3)):
      tbs = set() 
      tbs.add(table1)
      tbs.add(table2)
      tbs.add(table3)

      if (tbs not in confs):
        confs = confs + [tbs]

for x in confs:
  for i in x:
    print i
  print '---'
