package main

import (
	"fmt"
  "os"
  "strconv"
)

type tuple struct {
   x int
   y int
}

var dirs = []tuple {
  tuple {0, 1},
  tuple {-1, 0},
  tuple {0, -1},
  tuple {1, 0}}

func sum(cx int, cy int, m [2000][2000]int) int {
  return  m[cx-1][cy-1]+m[cx][cy-1]+m[cx+1][cy-1]+m[cx+1][cy]+m[cx-1][cy]+m[cx-1][cy+1]+m[cx][cy+1]+m[cx+1][cy+1]
}

func main() {
  val, _ := strconv.Atoi(os.Args[1])
  var m = [2000][2000]int{}
  xi, yi := 1000, 1000
  cx, cy, idx := xi, yi, 1

  curr_dir := dirs[0]
  next_dir := dirs[1]
  m[cx][cy] = 1

  for {
    cx += curr_dir.x
    cy += curr_dir.y

    m[cx][cy] = sum(cx, cy, m)

    if (m[cx][cy] > val) {
      fmt.Println(m[cx][cy]);
      break;
    }

    if (m[cx+next_dir.x][cy+next_dir.y] == 0) {
      idx++
      curr_dir = next_dir
      next_dir = dirs[idx % len(dirs)]
    }
  }
}
