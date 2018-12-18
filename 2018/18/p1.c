#include <stdio.h>
#include <memory.h>

#define GROUND '.'
#define TREE '|'
#define LUMBER '#'

char m[52][52];
char m1[52][52];

char shots[1000][52][52];

int count_t(int x, int y, char t) {
  int c = 0;
  for(int i = -1; i < 2; i++)
    for(int j = -1; j < 2; j++) {
      if (i == 0 && j == 0) continue;
      if (m[x+i][y+j] == t) {
        c++;
      }
    }


  return c;
}

int main() {
  int r = 1;
  int l = 0;
  int time = 0;

  memset(m, GROUND, 52*52);

  while(scanf("%s\n", m[r]+1) != -1) {
    r++;
  }

  l = strlen(m[1]);

  for(int t = 0; t < 10; t++) {
    
    memcpy(m1, m, 52*52);
    for(int i = 1; i < r; i++) {
      for(int j = 1; j < l; j++) {


        if (m[i][j] == GROUND && count_t(i, j, TREE) >= 3) m1[i][j] = TREE;
        if (m[i][j] == TREE && count_t(i, j, LUMBER) >= 3) m1[i][j] = LUMBER;
        if (m[i][j] == LUMBER && (count_t(i, j, TREE) < 1 || count_t(i, j, LUMBER) < 1)) m1[i][j] = GROUND;
      }
    }
    memcpy(m, m1, 52*52);
  }

  int w = 0, u = 0;
  for(int i = 1; i < r; i++) {
    for(int j = 1; j < l; j++) {
      if (m[i][j] == TREE) w++;
      if (m[i][j] == LUMBER) u++;
    }
  }

  printf("%d %d %d\n", w, u, w*u);
}
