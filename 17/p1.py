from itertools import combinations


with open("inputs/day_17_input.txt") as fin:
    sizes = [int(i) for i in fin.readlines()]

combos = [combo for n in range(1, len(sizes) + 1)
          for combo in combinations(sizes, n) if sum(combo) == 150]

print("{} total combinations".format(len(combos)))
print("{} minimal combinations"
      .format(sum(1 for combo in combos if len(combo) == len(combos[0]))))
