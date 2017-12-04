package main

import (
  "bufio"
  "fmt"
  "os"
  "strings"
)

func main() {
  scanner := bufio.NewScanner(os.Stdin)

  sum := 0
  for scanner.Scan() {
    s := scanner.Text()

    valid := true
    for i, a := range strings.Fields(s) {
      for j, b := range strings.Fields(s) {
        if i != j && a == b {
                valid = false
        }
      }
    }
        if valid {
         sum++;
        }
  }

  fmt.Println(sum)
}

