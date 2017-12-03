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
  for i, n := range s {
    if n == '(' {
      level++
    } else {
      level--
    }

    if level == -1 {
      fmt.Println(i + 1)
      break;
    }
  }
}
