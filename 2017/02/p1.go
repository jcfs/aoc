package main

import (
  "bufio"
  "fmt"
  "os"
  "strconv"
  "strings"
)

func main() {
  var diff int = 0

  scanner := bufio.NewScanner(os.Stdin)

  for scanner.Scan() {
    s := scanner.Text()
    var min, max int = 9000, 0

    for _, n := range strings.Fields(s) {
      d, _ := strconv.Atoi(n)
      if d > max {
        max = d
      }

      if d < min {
        min = d
      }
    }
    diff += max - min
  }

  fmt.Println(diff)
}
