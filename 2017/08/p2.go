package main

import (
  "fmt"
  "math"
)

var compMap = map[string] func(int, int) bool {
  "==": func(a int, b int) bool { return a == b},
  ">=": func(a int, b int) bool { return a >= b},
  "<=": func(a int, b int) bool { return a <= b},
  ">": func(a int, b int) bool { return a > b},
  "<": func(a int, b int) bool { return a < b},
  "!=": func(a int, b int) bool { return a != b}}

func main() {
  registers := make(map[string]int)
  max := 0
  for {
    var reg, op, cond_reg, comp string
    var val, amt int

    i, _ := fmt.Scanf("%s %s %d if %s %s %d\n", &reg, &op, &val, &cond_reg, &comp, &amt)

    if i == 0 {
      break
    }

    if (compMap[comp](registers[cond_reg], amt)) {
      if (op == "inc") {
        registers[reg] += val
      } else {
        registers[reg] -= val
      }

      max = int(math.Max(float64(max), float64(registers[reg])))
    }
  }
  fmt.Println(max)
}
