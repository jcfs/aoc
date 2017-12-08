package main

import (
  "fmt"
)

var comparison = map[string] func(int, int) bool {
  "==": func(a int, b int) bool { return a == b},
  ">=": func(a int, b int) bool { return a >= b},
  "<=": func(a int, b int) bool { return a <= b},
  ">":  func(a int, b int) bool { return a >  b},
  "<":  func(a int, b int) bool { return a <  b},
  "!=": func(a int, b int) bool { return a != b}}

func main() {
  regs := make(map[string]int)

  for {
    var reg, op, cond_reg, comp string
    var val, amt int

    i, _ := fmt.Scanf("%s %s %d if %s %s %d\n", &reg, &op, &val, &cond_reg, &comp, &amt)

    if i == 0 {
      break
    }

    if (comparison[comp](regs[cond_reg], amt)) {
      if (op == "inc") {
        regs[reg] += val
      } else {
        regs[reg] -= val
      }
    }
  }
  fmt.Println(regs)
}
