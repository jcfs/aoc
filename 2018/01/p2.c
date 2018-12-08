#include <stdio.h>

char freq[1000000];

int main() {
  int input[1000];
  int sum = 0, n = 0;
  freq[0] = 1;

  while(scanf("%d\n", &input[n++]) != -1);

  n = 0;
  while(1) {
    sum += input[n];
    n++;
    if (freq[sum+50000]) {
      printf("%d\n", sum);
      break;
    }

    if (n == 1000) n = 0;
    freq[sum+50000] = 1;
  }
}
