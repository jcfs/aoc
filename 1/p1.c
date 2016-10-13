#include <stdio.h>

int main(int argc, char ** argv) {

    int currentFloor = 0;
    char ch;

    while(ch = getchar()) {
	if (ch == '\n') break;
        ch == ')' ? currentFloor-- : currentFloor++;
   }

   printf("%d\n", currentFloor);
}
