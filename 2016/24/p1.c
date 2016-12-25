#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//*****************************************
// B QUEUE SPECIFIC CODE
//*****************************************
typedef struct {
  int32_t x;
  int32_t y;
} pair_t;

typedef struct node {
  pair_t p;
  uint32_t steps;
  struct node * next;
} node_t;

uint32_t q_size = 0;

node_t * head = NULL;
node_t * tail = NULL;

// add element to the end of the queue
void q_add(uint32_t x, uint32_t y, uint32_t steps) {
  node_t * n = calloc(1, sizeof(node_t));

  n->p.x = x;
  n->p.y = y;
  n->steps = steps;
  q_size++;

  if (head == NULL) {
    head = n;
    tail = n;
  } else {
    tail->next = n;
    tail = n;
  }
}

// get beginning of the queue and remove the element from there
node_t * q_get() {
  if (head != NULL) {
    q_size--;
    node_t * ret = head;
    head = head->next;
    return ret;
  }

  return NULL;
}

// checks if the queue is empty
int q_empty() {
  return head == NULL;
}

// clear the queue
void q_clear() {
  while(head != NULL) {
    free(q_get());
  }
}

/*****************************************
 END QUEUE SPECIFIC CODE
*****************************************/
char v[200][200], m[200][200], z[10];
uint32_t p[10][10];
pair_t pos[10];
int32_t min_p1 = 1000, min_p2;
int32_t MAX = 0;

// checks if the position is a valid position to travel
int valid(int32_t x, int32_t y) {
  return m[x][y] != '#' && !v[x][y];
}

// BFS implementation, with a queue
int BFS(int x, int y, int tx, int ty) {
  q_add(x, y, 0);

  while(!q_empty()) {
    node_t * n = q_get();

    if (n->p.x == tx && n->p.y == ty) {
      return n->steps;
    }

    if (valid(n->p.x, n->p.y+1)) {
      q_add(n->p.x, n->p.y+1, n->steps+1);
      v[n->p.x][n->p.y+1] = 1;
    }
    if (valid(n->p.x-1, n->p.y)) {
      q_add(n->p.x-1, n->p.y, n->steps+1);
      v[n->p.x-1][n->p.y] = 1;
    }
    if (valid(n->p.x, n->p.y-1)) {
      q_add(n->p.x, n->p.y-1, n->steps+1);
      v[n->p.x][n->p.y-1] = 1;
    }   
    if (valid(n->p.x+1, n->p.y)) {
      q_add(n->p.x+1, n->p.y, n->steps+1);
      v[n->p.x+1][n->p.y] = 1;
    }

    free(n);
  }

  return -1;
}

void sp(int y, int s, int cnt) {
  if (cnt == MAX) {
    if (s < min_p1) {
      min_p1 = s;
      // save last position to calculate part 2
      min_p2 = y;
    }
  }

  for(int j = 0; j < MAX + 1; j++) {
    if (!z[j] && p[y][j] > 0) {
      z[y] = 1;
      sp(j, s + p[y][j], cnt + 1);
      z[y] = 0;
    }
  }
}


int main(int argc, char ** argv) {
  int x1, y1, x2, y2, k = 0;

  // parse the input and get important values
  while(fgets(m[k++], 1000, stdin)) {
    for(int i = 0; i < strlen(m[k-1]); i++) {
      int c = m[k-1][i] - '0';
      if (c >= 0 && c <= 9 ) {
        pos[c].x = k-1;
        pos[c].y = i;
        if (c > MAX) {
          MAX = c;
        }
      }
    }
  }

  // calculate the minimum distance between all pairs
  for(char i = 0; i <= MAX - 1; i++) {
    for(char j = i+1; j <= MAX; j++) {
      pair_t a = pos[i];
      pair_t b = pos[j];

      memset(v, 0, 200 * 200 * sizeof(char));

      // clear the queue
      q_clear();

      int min = BFS(a.x, a.y, b.x, b.y);

      printf("Distance from %1d at (%3d,%3d) to %1d at (%3d,%3d) distance = %5d\n", i, a.x, a.y, j, b.x, b.y, min);

      p[i][j] = p[j][i] = min;
    }
  }

  // brute force and find the sum of the minimum in all pairs
  sp(0, 0, 0);

  printf("part 1 %d\n", min_p1);
  // this is a bit lucky I guess...
  printf("part 2 %d\n", min_p1 + p[min_p2][0]);

}
