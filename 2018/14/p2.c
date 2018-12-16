#include <stdio.h>
#include <string.h>

char r[100000000];

int main() {
  int e1 = 0;
  int e2 = 1;
  int k = 2;

  r[0] = 3+'0';
  r[1] = 7+'0';

  char * u = "170641\0";
  int len = strlen(u);

  for(;;) { 
    int y = (r[e1]-'0') + (r[e2]-'0');
    int  ki = k;

    if (y > 9) {
      int s = y % 10;
      int f = (y/10) % 10;

      r[k] = f + '0';
      r[k+1] = s + '0';
      k += 2;
    } else {
      r[k] = y + '0';
      k += 1;
    }

    e1 = (e1 + r[e1]-'0' + 1) % k; 
    e2 = (e2 + r[e2]-'0' + 1) % k;

    char * p;

    if ((p=strstr(r+ki - len, u)) != NULL) {
      printf("%d\n", ki - len);
      break;
    }
  }
}
