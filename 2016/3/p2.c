#include <stdio.h>

int main(int argc, char **argv) {
  int a1, b1, c1;
  int a2, b2, c2;
  int a3, b3, c3;
  int count = 0;

  while(scanf("%d %d %d\n%d %d %d\n%d %d %d", &a1, &a2, &a3, &b1, &b2, &b3, &c1, &c2, &c3) == 9) {
    if (a1+b1 > c1 && b1+c1 > a1 && a1+c1 > b1) count++;
    if (a2+b2 > c2 && b2+c2 > a2 && a2+c2 > b2) count++;
    if (a3+b3 > c3 && b3+c3 > a3 && a3+c3 > b3) count++;
  }

  printf("%d\n", count);
}
