package main

import (
  "fmt"
)

func main() {
  input := "206,63,255,131,65,80,238,157,254,24,133,2,16,0,1,3"
  arr := []int{};
  ascii := []int{};
  currentPosition, skipSize := 0, 0

  for i := 0; i < len(input); i++ {
    ascii = append(ascii, int(input[i]))
  }

  ascii = append(ascii, 17);
  ascii = append(ascii, 31);
  ascii = append(ascii, 73);
  ascii = append(ascii, 47);
  ascii = append(ascii, 23);

  for i := 0; i <= 255; i++ {
    arr = append(arr, i);
  }

  for k := 0; k < 64; k++ {
    for _, i := range ascii {
      for j := 0; j < i/2; j++ {
        t := arr[(currentPosition+j) % len(arr)]
        arr[(currentPosition+j) % len(arr)] = arr[(currentPosition+i-j-1) % len(arr)]
        arr[(currentPosition+i-j-1) % len(arr)] = t
      }
      currentPosition += i + skipSize;
      skipSize++;
    }
  }

  for val, i := 0, 0; i < 16; i++ {
    for j := 0; j < 16; j++ {
      val = val ^ arr[i*16+j];
    }
    fmt.Printf("%x", val);
  }
}
