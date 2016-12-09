/* compile gcc -o p2 p2.c -Wall */
#include <stdio.h>
#include <string.h>

long calculate(char * s, int len) {
  long total = 0;

  for(char * is = s; s - is < len;) {
    int r, g;

    if (sscanf(s, "(%dx%d)", &r, &g) == 2) {
      char * e = strchr(s, ')') + 1;
      total += calculate(e, r) * g;
      s = e + r;
    } else {
      total++;
      s++;
    }
  }

  return total;
}

int main(int argc, char ** argv) {
  char line[64335];

  if (fgets(line, 64335, stdin) != NULL) 
    printf("%ld\n", calculate(line, strlen(line)-1));
}
