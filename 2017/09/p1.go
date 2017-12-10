package main

import (
  "regexp"
  "bufio"
  "fmt"
  "os"
)

func main() {
  depth, sum := 0, 0
  reader := bufio.NewReader(os.Stdin)
  s, _ := reader.ReadString('\n')

  s = regexp.MustCompile("!.").ReplaceAllString(s, "")
  s = regexp.MustCompile("<.*?>").ReplaceAllString(s, "")

  for i := 0; i < len(s); i++ {
    if s[i] == '{' {
      depth++
    } else if s[i] == '}' {
      sum += depth
      depth--
    }
  }

  fmt.Println(sum)
}
