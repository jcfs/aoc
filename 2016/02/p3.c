#include <stdio.h>
#include <string.h>

int turn[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

int pad[5][5] = {
  {'0', '0', '1', '0', '0'},
  {'0', '2', '3', '4', '0'},
  {'5', '6', '7', '8', '9'},
  {'0', 'A', 'B', 'C', '0'},
  {'0', '0', 'D', '0', '0'}
};

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
      x = clamp(0, 4, x + turn[get_turn(line[i])][0]);
      y = clamp(0, 4, y + turn[get_turn(line[i])][1]);

      if (pad[x][y] == '0') {
        x = clamp(0, 4, x + turn[get_turn(line[i])][0]*-1);
        y = clamp(0, 4, y + turn[get_turn(line[i])][1]*-1);
      }
    }

    printf("%c", pad[x][y]);
  }

  printf("\n");

  return 0;
}
