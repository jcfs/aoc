/* compile gcc -o p2 p2.c -Wall */
#include <stdio.h>
#include <string.h>

long calculate(char * s, int len) {
  long total = 0;
  int i = 0;

  while(i < len) {
    int r, g;
    if (s[i] == '(' && sscanf(s+i, "(%dx%d)", &r, &g) == 2) {
      char * k = strchr(s+i, ')') + 1;    

      total += calculate(k, r) * g;

      // skip the calculated characters and the brackets stuff
      i += r + (k - (s + i));
    } else {
      i++;
      total++;
    }

  }
  return total;
}

int main(int argc, char ** argv) {
  char line[64335];

  if (fgets(line, 64335, stdin) != NULL) 
    printf("%ld\n", calculate(line, strlen(line) - 1));
}
