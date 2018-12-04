// input tweak: cat in | sort | sed s/Guard\ //g | sed s/\ up//g | sed s/\ asleep//g | sed s/\ begins\ shift//g
#include <stdio.h>
#include <stdlib.h>

// 4000 guards should be enough
int si[4000][60];

int main() {
  char g[100], s[100];
  int h, m, currentGuard, currentMin;

  while(scanf("%s %d:%d] %s", g, &h, &m, s) != -1) {
    if (s[0] == '#') {
      sscanf(s+1, "%d", &currentGuard);
      currentMin = m;
    } else if (s[0] == 'w') {
      for(int i = currentMin; i < m; i++) {
        si[currentGuard][i]++;
      }
    } else if (s[0] == 'f') {
      currentMin = m;
    }
  }

  int mx = 0, hm = 0, hg = 0;

  for(int i = 0; i < 4000; i++) {
    for(int j = 0; j < 60; j++) {
      if (si[i][j] > mx) {
        mx = si[i][j];
        hm = j;
        hg = i;
      }
    }
  }

  printf("%d %d %d\n", hm, hg, hm*hg);

}
