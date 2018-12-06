#include <stdio.h>
#include <math.h>

typedef struct n {
  int x, y;
  char id;
  char inf;
  int count;
} node;

node nodes[100];
char grid[1000][1000];

// manhattan distance 
int dist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}

// all the nodes that have expanded to the grid edges are considered
// infinits
void mark_infinites(int max_x, int max_y) {
  for(int i = 0; i <= max_x; i++) {
    nodes[grid[i][0]].inf = 1;
    nodes[grid[i][max_y]].inf = 1;
  }

  for(int i = 0; i <= max_y; i++) {
    nodes[grid[0][i]].inf = 1;
    nodes[grid[max_x][i]].inf = 1;
  }
}

int main(int argc, char ** argv) {
  int number = 0;
  int x, y, max_x = 0, max_y = 0;
  unsigned min_x = -1, min_y = -1;

  while(scanf("%d, %d\n", &x, &y) != -1) {
    nodes[number].x = x;
    nodes[number].y = y;
    nodes[number].id = number++;
    
    if (x > max_x) max_x = x;
    if (y > max_y) max_y = y;
  }

  for(int i = 0; i <= max_x; i++) {
    for(int j = 0; j <= max_y; j++) {
      unsigned c_min = -1;
      unsigned d_min = -1;
      int duplicates = 0;

      for(int k = 0; k < number; k++) {
        int d = dist(nodes[k].x, nodes[k].y, i, j);

        if (d == d_min) {
          duplicates++;
        } else if (d < d_min) {
          duplicates = 0;
          d_min = d;
          c_min = nodes[k].id;
        }
      }

      if (!duplicates) {
        nodes[c_min].count++;
        grid[i][j] = c_min;
      }
    }
  }

  mark_infinites(max_x, max_y);

  int max = 0;
  for(int k = 0; k < number; k++) {
    if (!nodes[k].inf && nodes[k].count > max)
      max = nodes[k].count;
  }

  printf("%d\n", max);
}
