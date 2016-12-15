#include <stdio.h>
#include <string.h>

int pad[5][5] = {
  {'0', '0', '1', '0', '0'},
  {'0', '2', '3', '4', '0'},
  {'5', '6', '7', '8', '9'},
  {'0', 'A', 'B', 'C', '0'},
  {'0', '0', 'D', '0', '0'}
};

int main(int argc, char ** argv) {

  char line[64000];
  int x = 0, y = 2;
  int i = 0;

  while(fgets(line, 64000, stdin) != NULL) {
    for(i = 0; i < strlen(line) - 1; i++) {
      if (line[i] == 'U') y--;
      if (line[i] == 'L') x--;
      if (line[i] == 'R') x++;
      if (line[i] == 'D') y++;

      if (x < 0) x = 0;
      if (x > 4) x = 4;
      if (y < 0) y = 0;
      if (y > 4) y = 4;

      if (pad[y][x] == '0') {
        if (line[i] == 'U') y++;
        if (line[i] == 'L') x++;
        if (line[i] == 'R') x--;
        if (line[i] == 'D') y--;
      }
    }

    printf("%c", pad[y][x]);
  }

  printf("\n");

  return 0;
}
