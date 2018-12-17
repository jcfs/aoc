#include <stdio.h>

#define WALL '#'
#define WATER '~'
#define DRY '|'
#define SAND '.'

char map[3000][3000];

char is_bottom(char ch) {
  return ch == WALL || ch == WATER;
}

char is_water(char ch) {
  return ch == WATER;
}

int main() {
  char f, s;
  int rmin, rmax, l;
  int ymax = 0, xmin = 9999, xmax = 0;

  for(int i = 0; i < 3000; i++)
    for(int j = 0; j < 3000; j++)
      map[i][j] = SAND;

  map[0][500] = DRY;

  while(scanf("%c=%d, %c=%d..%d\n", &f, &l, &s, &rmin, &rmax) != -1) {
    if (s == 'x') {
      for(int i = rmin; i <= rmax; i++)
        map[l][i] = WALL;

      if (l > ymax)
        ymax = l;

      if (rmin < xmin) xmin = rmin;
      if (rmax > xmax) xmax = rmax;
    } else {
      for(int i = rmin; i <= rmax; i++)
        map[i][l] = WALL;

      if (l < xmin) xmin = l;
      if (l > xmax) xmax = l;

      if (rmax > ymax)
        ymax = rmax;
    }
  }

  char c = 1;

  while(c) {
    c = 0;

    for(int y = 0; y <= ymax; y++) {
      for(int x = xmin - 2; x <= xmax + 2; x++) {

        if (map[y][x] == DRY) {
          if (map[y+1][x] == SAND) {
            map[y+1][x] = DRY;
            c = 1;
          } else if (is_bottom(map[y+1][x])) {

            char lb = 0, rb = 0;
            int lbi = 0, rbi = 0, step = 1;

            // process left bound
            while(map[y][x-step] != WALL && is_bottom(map[y+1][x-step])) {
              if (map[y][x-step] == SAND) {
                map[y][x-step] = DRY;
                c = 1;
              }
              step++;
            }

            if (map[y][x-step] == WALL) {
              lb = 1;
              lbi = -step;
            } else if (map[y][x-step] == SAND) {
              map[y][x-step] = DRY;
              c = 1;
            }

            step = 1;

            // process right bound
            while(map[y][x+step] != WALL && is_bottom(map[y+1][x+step])) {
              if (map[y][x+step] == SAND) {
                map[y][x+step] = DRY;
                c = 1;
              }
              step++;
            }

            if (map[y][x+step] == WALL) {
              rb = 1;
              rbi = step;
            } else if (map[y][x+step] == SAND) {
              map[y][x+step] = DRY;
              c = 1;
            }

            // we are within bounds
            if (lb && rb) {
              for (int r = lbi + 1; r < rbi; r++) {
                if (map[y][x+r] != WATER) {
                  map[y][x+r] = WATER;
                  c = 1;
                }
              }
            }
          }
        } 
      }
    }
  }

  int t = 0;
  for(int y = 0; y <= ymax; y++) {
    for(int x = 0; x < 3000; x++) {
      if (is_water(map[y][x]))
        t++;
    }
  }

  printf("%d\n", t);

}
