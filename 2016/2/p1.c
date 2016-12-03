#include <stdio.h>
#include <string.h>

int turn[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

int get_turn(char ch) {
  if (ch == 'L') return 3;
  else if (ch == 'D') return 1;
  else if (ch == 'R') return 0;
  else return 2;
}

int clamp(int min, int max, int value) {
  return (value < min) ? min : (value > max) ? max : value;
}

int main(int argc, char ** argv) {

  char line[64000];
  int x = 1, y = 1;
  int i = 0;

  while(fgets(line, 64000, stdin) != NULL) {
    for(i = 0; i < strlen(line) - 1; i++) {
      x = clamp(0, 2, x + turn[get_turn(line[i])][0]);
      y = clamp(0, 2, y + turn[get_turn(line[i])][1]);
    }

    printf("%d", y*3 + x + 1);
  }

  printf("\n");

  return 0;
}
