#include <stdio.h>

int m[10000][10000];

int main() {
  int e, x, y, w, h;
  int cnt = 0;

  while(scanf("#%d @ %d,%d: %dx%d\n", &e, &x, &y, &w, &h) != -1) 
    for(int i = 0; i < w; i++) 
      for(int j = 0; j < h; j++) {
        m[x+i][y+j]++;
        if (m[x+i][y+j] == 2) 
          cnt++;
      }

  printf("%d\n", cnt);
}
