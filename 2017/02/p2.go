package main

import (
  "bufio"
  "fmt"
  "os"
  "strconv"
  "strings"
)

func main() {
  scanner := bufio.NewScanner(os.Stdin)

  diff := 0
  for scanner.Scan() {
    s := scanner.Text()

    for i, a := range strings.Fields(s) {
      for j, b := range strings.Fields(s) {
        d1, _ := strconv.Atoi(a)
        d2, _ := strconv.Atoi(b)

        if i != j && d1%d2 == 0 {
          diff += d1 / d2
        }
      }
    }
  }

  fmt.Println(diff)
}
