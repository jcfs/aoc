#include <stdio.h>

int sum = 0;

int proc() {
  int c, m;
  scanf("%d %d", &c, &m);

  for(int i = 0; i < c; i++) {
    proc();
  }

  for(int i = 0; i < m; i++) {
    int t = 0;
    scanf("%d", &t);
    sum += t;
  }

  return 0;
}

int main() {
  proc();
  printf("%d\n", sum);
}
