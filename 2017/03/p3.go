package main

import (
  "fmt"
  "os"
  "strconv"
  . "../common"
)

func sum(cx int, cy int, m [2000][2000]int) int {
  return  m[cx-1][cy-1]+m[cx][cy-1]+m[cx+1][cy-1]+m[cx+1][cy]+m[cx-1][cy]+m[cx-1][cy+1]+m[cx][cy+1]+m[cx+1][cy+1]
}

func main() {
  directions := []Tuple { Tuple {0, 1}, Tuple {1, 0}, Tuple {0, -1}, Tuple {-1, 0} }

  initialPosition, m := Tuple{1000, 1000}, [2000][2000]int{}
  currentPosition := initialPosition
  directionsIndex, i := 0, 1
  argument, _ := strconv.Atoi(os.Args[1])

  // initialize directions
  currentDirection := directions[directionsIndex]
  nextDirection := directions[directionsIndex + 1]

  for ; i < argument; {
    m[currentPosition.X][currentPosition.Y] = i
    // we if have an empty space on the next adjacent direction
    // we change direction
    if (m[currentPosition.X+nextDirection.X][currentPosition.Y+nextDirection.Y] == 0) {
      directionsIndex++
      currentDirection = nextDirection
      nextDirection = directions[directionsIndex % len(directions)]
    }
    currentPosition.Add(currentDirection)
    i = sum(currentPosition.X, currentPosition.Y, m);
    fmt.Printf("next will be %d,%d = %d %v\n", currentPosition.X, currentPosition.Y, i, currentDirection)


  }

  fmt.Println(i)
}
