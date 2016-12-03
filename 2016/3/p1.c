#include <stdio.h>

int main(int argc, char **argv) {
  int a, b, c;
  int count = 0;

  while(scanf("%d %d %d\n", &a, &b, &c) == 3) {
    if (a+b > c && b+c > a && a+c > b) {
      count++;
    }
  }

  printf("%d\n", count);
}
