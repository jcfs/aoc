/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>
#include <string.h>

char line[64335];

int main(int argc, char ** argv) {
  long total = 0;
  
  if (fgets(line, 64335, stdin) != NULL) {
    char * k = line;

    for(k = line; *k != '\n'; k++) {
      int r, g;
      if (sscanf(k, "(%dx%d)", &r, &g) == 2) {
        total += r * g;
        k = strchr(k, ')') + r;
      } else {
        total++;
      }
    }
    printf("%ld\n", total);
  } 
}
