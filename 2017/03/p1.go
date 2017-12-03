package main

import (
  "fmt"
  "os"
  "strconv"
  . "../common"
)

func main() {
  directions := []Tuple { Tuple {0, 1}, Tuple {-1, 0}, Tuple {0, -1}, Tuple {1, 0} }

  initialPosition, m := Tuple{1000, 1000}, [2000][2000]int{}
  currentPosition := initialPosition
  directionsIndex := 0
  argument, _ := strconv.Atoi(os.Args[1])

  // initialize directions
  currentDirection := directions[directionsIndex]
  nextDirection := directions[directionsIndex + 1]

  for i := 1; i < argument; i++ {
    m[currentPosition.X][currentPosition.Y] = i
    // we if have an empty space on the next adjacent direction
    // we change direction
    if (m[currentPosition.X+nextDirection.X][currentPosition.Y+nextDirection.Y] == 0) {
      directionsIndex++
      currentDirection = nextDirection
      nextDirection = directions[directionsIndex % len(directions)]
    }

    currentPosition.Add(currentDirection)
  }

  fmt.Println(currentPosition.Dist(initialPosition))
}
