#include <stdio.h>
#include <math.h>

typedef struct n {
  int x, y;
  char id;
  char inf;
  int count;
} node;


node nodes[100];

int dist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}

int main() {
  int number = 0;
  int x, y, mx = 0, my = 0;

  while(scanf("%d, %d\n", &x, &y) != -1) {
    nodes[number].x = x;
    nodes[number].y = y;
    nodes[number].id = number+1;
    number++;

    if (x > mx) mx = x;
    if (y > my) my = y;
  }

  int cnt = 0;
  for(int i = 0; i < mx; i++) {
    for(int j = 0; j < my; j++) {
      int sum = 0;
      for(int k = 0; k < number; k++) {
        int d = dist(nodes[k].x, nodes[k].y, i, j);
        sum += d;        
      }

      if (sum < 10000) 
        cnt++;
    }
  }

  printf("%d\n", cnt);
}


