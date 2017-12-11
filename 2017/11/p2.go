package main

import (
  "bufio"
  "fmt"
  "os"
  "strings"
  "math"
)

type cube struct {
  x, y, z int
}

var directions = map[string] func(c *cube) {
  "n": func(c *cube) { c.y++; c.z--; },
  "ne": func(c *cube) { c.z--; c.x++; },
  "se": func(c *cube) { c.x++; c.y--; },
  "s": func(c *cube) { c.y--; c.z++; },
  "sw": func(c *cube) { c.z++; c.x--; },
  "nw": func(c *cube) { c.y++; c.x--; }}

func distance(c cube) int {
  return int((math.Abs(float64(c.x))+math.Abs(float64(c.y))+math.Abs(float64(c.z))) / 2)

}

func main() {
  scanner := bufio.NewScanner(os.Stdin)
  var c cube
  var max int
  for scanner.Scan() {
    s := scanner.Text()
    a := strings.Split(s, ",")
    for _, n := range a {
      directions[n](&c)
      if (distance(c) > max) {
        max = distance(c)
      }
    }
  }

  fmt.Println(max);
}
