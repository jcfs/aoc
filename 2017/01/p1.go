package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	s, _ := reader.ReadString('\n')
	s = strings.TrimSpace(s)

	sum := 0
	for i := 0; i < len(s); i++ {
		if s[i] == s[(i+1)%len(s)] {
			sum += int(s[i] - '0')
		}
	}

	fmt.Println(sum)
}
