#include <stdio.h>
#include <stdlib.h>

typedef struct bo {
  int x, y, z;
  int r;
} bot;

bot bots[10000];

int cmp(const void * a, const void * b) {
  bot * ba = (bot *) a;
  bot * bb = (bot *) b;
  return bb->r - ba->r;
}

int mhd(bot * a, bot * b) {
  return abs(a->x - b->x) + abs(a->y - b->y) + abs(a->z - b->z);
}

int main() {
  int n = 0;

  while(scanf("pos=<%d,%d,%d>, r=%d\n", &bots[n].x, &bots[n].y, &bots[n].z, &bots[n].r) != -1) {
    n++;
  }

  qsort(bots, n, sizeof(bot), cmp);

  int m = bots[0].r;
  int cnt = 0;

  for(int i = 0; i < n; i++) {
    int d = mhd(&bots[0], &bots[i]);
    printf("%d %d\n", m, d);
    if (d <= m) {
      cnt++;  
    }
  }

  printf("%d\n", cnt);
}
