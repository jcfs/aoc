/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
  char line[64335];

  if (fgets(line, 64335, stdin) != NULL) {
    long total = 0;

    char * k = line;
    char * ok = line;

    // extreme case when there are no brackets at all
    if (!strchr(k, '(')) 
      total += strlen(line);

    while((k = strchr(ok, '(')) != NULL) {
      // sum the amount before the bracket to the total length
      total += (k - ok);

      int r, g;
      if (sscanf(k, "(%dx%d)", &r, &g) == 2) {
        total += r * g;
        k = strchr(k, ')') + r;    
      }

      ok = k;
    }

    printf("%ld\n", total);
  } 
}
