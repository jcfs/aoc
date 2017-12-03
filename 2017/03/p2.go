package main

import (
  "fmt"
  "os"
  "strconv"
  . "../common"
)

func sumArround(point Tuple, m [2000][2000]int) int {
  result := -m[point.X][point.Y]
  for i := point.X - 1; i < point.X + 2;  i++ {
    for j := point.Y - 1; j < point.Y + 2;  j++ {
      result += m[i][j];
    }
  }

  return result
}

func main() {
  directions := []Tuple { Tuple {0, 1}, Tuple {-1, 0}, Tuple {0, -1}, Tuple {1, 0} }

  initialPosition, m := Tuple{1000, 1000}, [2000][2000]int{}
  currentPosition := initialPosition
  directionsIndex, i := 0, 1
  argument, _ := strconv.Atoi(os.Args[1])

  // initialize directions
  currentDirection := directions[directionsIndex]
  nextDirection := directions[directionsIndex+1]
  directionsIndex++

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
    i = sumArround(currentPosition, m);
  }

  fmt.Println(i)
}
