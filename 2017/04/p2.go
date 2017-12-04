package main

import (
  "bufio"
  "fmt"
  "os"
  "strings"
  "sort"
)

func SortString(w string) string {
  s := strings.Split(w, "")
  sort.Strings(s)
  return strings.Join(s, "")
}

func isAnagram(a string, b string) bool {
  return SortString(a) == SortString(b)
}

func main() {
  scanner := bufio.NewScanner(os.Stdin)

  sum := 0
  for scanner.Scan() {
    s := scanner.Text()

    valid := true
    for i, a := range strings.Fields(s) {
      for j, b := range strings.Fields(s) {
        if i != j && isAnagram(a, b) {
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

