#include <stdio.h>

int main(int argc, char ** argv) {

    int currentFloor = 0;
    int currentIndex = 1;
    char ch;

    while(ch = getchar()) {
        ch == ')' ? currentFloor-- : currentFloor++;

        if (currentFloor == -1) {
            printf("%d\n", currentIndex);
            break;
        }
        currentIndex++;
    }
}
