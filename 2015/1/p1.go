package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	s, _ := reader.ReadString('\n')
  level := 0
  for _, n := range s {
    if n == '(' {
      level++
    } else {
      level--
    }
  }

  fmt.Println(level)
}
