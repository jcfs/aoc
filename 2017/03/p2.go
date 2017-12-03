package main

import (
  "fmt"
  "os"
  "strconv"
  . "../common"
)

// sum all the numbers in the cells arround the given point
// represented by a Tuple{x, y}
func sumArround(point Tuple, m *[2000][2000]int) int {
  result := -(*m)[point.X][point.Y]
  for i := -1; i < 2; i++ {
    for j := -1; j < 2; j++ {
      result += (*m)[point.X+i][point.Y+j];
    }
  }

  return result
}

func main() {
  directions := []Tuple { Tuple {0, 1}, Tuple {-1, 0}, Tuple {0, -1}, Tuple {1, 0} }

  initialPosition, m := Tuple{1000, 1000}, [2000][2000]int{}
  currentPosition := initialPosition
  directionsIndex, i := 1, 1
  argument, _ := strconv.Atoi(os.Args[1])

  // initialize directions
  currentDirection := directions[directionsIndex-1]
  nextDirection := directions[directionsIndex]

  for i < argument {
    m[currentPosition.X][currentPosition.Y] = i

    // we if have an empty space on the next adjacent direction
    // we change direction
    if (m[currentPosition.X+nextDirection.X][currentPosition.Y+nextDirection.Y] == 0) {
      directionsIndex++
      currentDirection = nextDirection
      nextDirection = directions[directionsIndex % len(directions)]
    }

    currentPosition.Add(currentDirection)
    i = sumArround(currentPosition, &m);
  }

  fmt.Printf("%v at %v\n", i, currentPosition)
}
