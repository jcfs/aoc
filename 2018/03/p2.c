#include <stdio.h>

int m[1000][1000];
int s[1400];

int main() {
  int e, x, y, w, h;
  long cnt = 0;
  while(scanf("#%d @ %d,%d: %dx%d\n", &e, &x, &y, &w, &h) != -1) {
    for(int i = 0; i < w; i++) {
      for(int j = 0; j < h; j++) {
        if (m[x+i][y+j]) {
          s[e] = 1;
          s[m[x+i][y+j]] = 1;	
        }
        m[x+i][y+j] = e;
      }
    }
  }

  for(int i = 1; i < 1350; i++) {
    if (!s[i]) printf("%d\n", i);
  }
}
