#include <stdio.h>

typedef struct p {
  int x, y;
  int vx, vy;
} point;

point s[1000];

int main() {
  int p = 0;
  int x, y, vx, vy;

  while(scanf("position=<%d,%d>velocity=<%d,%d>\n", &x, &y, &vx, &vy) != -1) {
    s[p].x=x;
    s[p].y=y;
    s[p].vx=vx;
    s[p].vy=vy;
    p++;
  }

  unsigned long dx_min = -1, d_min = -1;
  int h = 0;
  while(1) {

    int y_min, x_min, y_max, x_max;
    x_max = y_max = 0;
    y_min = 10000000;
    x_min = 10000000;

    for(int k = 0; k < p; k++) {
      s[k].x += s[k].vx;
      s[k].y += s[k].vy;

      if (s[k].x < x_min) x_min = s[k].x;
      if (s[k].y < y_min) y_min = s[k].y;
      if (s[k].x > x_max) x_max = s[k].x;
      if (s[k].y > y_max) y_max = s[k].y;
    }

    if (((x_max - x_min) * (y_max-y_min)) < d_min) {
      d_min = ((x_max - x_min) * (y_max-y_min));
      printf("new min %d %d\n", d_min, h);

      if (d_min < 1000) {
        for(int i = y_min; i <= y_max; i++) {
          for(int j = x_min; j <= x_max; j++) {
            int u = 0;
            for(int r = 0; r < p; r++)
              if (s[r].x == j && s[r].y == i) u=1;
            if (u)printf("#");
            else printf(".");
          }
          printf("\n");
        }
        return 1;
      }
    }

    h++;
  }
}
