/*
 Improved version after learning a little bit more about go
*/
package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func solve(s string, o int) int {
	sum := 0

	for i, n := range s {
		if byte(n) == s[(i+o)%len(s)] {
			sum += int(n - '0')
		}
	}

	return sum
}

func main() {
	s, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	s = strings.TrimSpace(s)

	fmt.Println(solve(s, 1))
	fmt.Println(solve(s, len(s)/2))
}
