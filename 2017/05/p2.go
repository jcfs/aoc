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

  for pc >= 0 && pc < len(s) {
    t := pc
    pc += s[pc]

    if (s[t] >= 3) {
      s[t]--
    } else {
      s[t]++
    }

    steps++
  }

  fmt.Println(steps)
}
