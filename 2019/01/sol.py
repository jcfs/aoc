with open('in') as lines:
    p1, p2 = 0, 0
    for line in lines:
        fuel = int(int(line) / 3) - 2
        p1 += fuel
        while fuel >= 0:
            p2 += fuel
            fuel = (int(fuel / 3)) - 2

    print("p1: ", p1, " p2: ", p2)
