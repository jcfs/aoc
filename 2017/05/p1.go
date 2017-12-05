package main

import (
  "fmt"
)

func main() {
  var val, pc, steps = 0, 0, 0
  var s []int

  for {
    i, _ := fmt.Scanf("%d\n", &val)

    if i == 0 {
      break
    }
    s = append(s, val)
  }

  for i := 0; i < len(s); i=pc {
    pc += s[i]
    s[i]++

    steps++
    if (pc < 0 || pc > len(s)) {
      break
    }
  }

  fmt.Println(steps)
}
