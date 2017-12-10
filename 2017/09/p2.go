package main

import (
  "regexp"
	"bufio"
	"fmt"
	"os"
)

func main() {
  sum := 0
	reader := bufio.NewReader(os.Stdin)
	s, _ := reader.ReadString('\n')

  s = regexp.MustCompile("!.").ReplaceAllString(s, "")

  inside := false
  for i := 0; i < len(s); i++ {
    if !inside && s[i] == '<' {
      inside = true
    } else if inside && s[i] != '>' {
      sum++
    } else if inside && s[i] == '>' {
      inside = false
    }
  }

	fmt.Println(sum)
}
