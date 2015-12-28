#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {

  int l = 2, i, j;
  long long p = 20151125;

  while (1) {
    for (i = l, j = 1; i > 0; i--, j++) {
      p = p * 252533 % 33554393;
      if (i == 2947 && j == 3029) {
        printf("%lld\n", p);
        exit(0);
      }
    }
    l++;
  }
}
