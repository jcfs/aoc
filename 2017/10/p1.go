package main

import (
  "fmt"
)

func main() {
  input := []int{206,63,255,131,65,80,238,157,254,24,133,2,16,0,1,3}
  //input := []int{3,4,1,5}
  arr := []int{};
  currentPosition, skipSize := 0, 0

  for i := 0; i <= 255; i++ {
    arr = append(arr, i);
  }

  for _, i := range input {

    for j := 0; j < i/2; j++ {
      t := arr[(currentPosition+j) % len(arr)]
      arr[(currentPosition+j) % len(arr)] = arr[(currentPosition+i-j-1) % len(arr)]
      arr[(currentPosition+i-j-1) % len(arr)] = t
    }
    fmt.Println(arr);

    currentPosition = (currentPosition + i + skipSize) % len(arr);
    skipSize++;
  }

  fmt.Println(arr[0]*arr[1]);
}
