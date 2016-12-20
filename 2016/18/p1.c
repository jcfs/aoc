/* compile gcc -o p1 p1.c -O3 -Wall */
/* solution for part 1 and 2 */
#include <stdio.h>
#include <string.h>

char map[2][1000];

int solve(char * in, int iter) {
  int count = 0;

  for(int  i = 0; i < strlen(in); i++) {
    map[0][i+1] = in[i];
    if (in[i] == '.') count++;
  }

  char * p1 = map[0];
  char * p2 = map[1];

  for(int i = 0; i < iter - 1; i++) {
    for(int j = 1; j <= strlen(in); j++) {
      int a = 0, b = 0, c = 0;

      a = p1[j-1];
      b = p1[j];
      c = p1[j+1];

      if (!a) a = '.';
      if (!c) c = '.';

      if (a != c) p2[j] = '^';
      else {
        p2[j] = '.';
        count++;  
      }

    }
    
    char * p3 = p1;
    p1 = p2;
    p2 = p3;
  }

  return count;
}


int main(int argc, char ** argv) {
  char * input = ".^^^^^.^^.^^^.^...^..^^.^.^..^^^^^^^^^^..^...^^.^..^^^^..^^^^...^.^.^^^^^^^^....^..^^^^^^.^^^.^^^.^^";
  printf("Part 1: %d\n", solve(input,40));
  printf("Part 2: %d\n", solve(input, 400000));
}
