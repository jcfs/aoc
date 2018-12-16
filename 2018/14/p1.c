#include <stdio.h>

char r[10000000];

int main() {
  int e1 = 0;
  int e2 = 1;
  int k = 2;

  r[0] = 3;
  r[1] = 7;

  for(int i = 0; i < 170641; i++) {
    int y = r[e1] + r[e2]; 
    if (y > 9) {
      int s = y % 10;
      y /= 10;
      int f = y % 10;

      r[k] = f;
      r[k+1] = s;
      k += 2;
    } else {
      r[k] = y;
      k += 1;
    }

    e1 = (e1 + r[e1] + 1) % (k); 
    e2 = (e2 + r[e2] + 1) % (k);
  }

  for(int i = 170641; i < 170641 + 10; i++)
    printf("%d", r[i]); 
}
