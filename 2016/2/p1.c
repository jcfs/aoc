#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {

  char line[64000];
  int x = 1, y = 1;
  int i = 0;

  while(fgets(line, 64000, stdin) != NULL) {
    for(i = 0; i < strlen(line) - 1; i++) {
      if (line[i] == 'U') y--;
      if (line[i] == 'L') x--;
      if (line[i] == 'R') x++;
      if (line[i] == 'D') y++;

      if (x < 0) x = 0;
      if (x > 2) x = 2;
      if (y < 0) y = 0;
      if (y > 2) y = 2;
    }

    printf("%d", y*3 + x + 1);
  }

  printf("\n");

  return 0;
}
