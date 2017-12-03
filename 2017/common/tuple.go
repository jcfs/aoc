package Tuple

import (
  "math"
)

// structure that will old the Tuple
type Tuple struct {
  X int
  Y int
}

// add operation on the Tuple structure
func (a *Tuple) Add(b Tuple) {
  a.X += b.X
  a.Y += b.Y
}

// manhattan distance between Tuples
func (a Tuple) Dist(b Tuple) int {
  return int(math.Abs(float64(b.X-a.X))+math.Abs(float64(b.Y-a.Y)))
}
