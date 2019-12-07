from collections import defaultdict
a = defaultdict(list)

def bfs(graph, start, goal):
    explored = []
    queue = [[start]]
 
    if start == goal:
        return None
 
    while queue:
        path = queue.pop(0)
        node = path[-1]
        if node not in explored:
            neighbours = graph[node]
            for neighbour in neighbours:
                new_path = list(path)
                new_path.append(neighbour)
                queue.append(new_path)
                if neighbour == goal:
                    return new_path
 
            explored.append(node)
    return None

for x in open('in').readlines():
  s, p = x.strip().split(')')
  a[s].append(p)
  a[p].append(s)

print(bfs(a, 'YOU', 'SAN'))
print(len(bfs(a, 'YOU', 'SAN')) - 3)
