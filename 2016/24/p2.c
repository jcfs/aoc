#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
  uint32_t x;
  uint32_t y;
  uint32_t steps;
  struct node * next;
} node_t;

node_t * head = NULL;
node_t * tail = NULL;
uint32_t q_size = 0;

void q_add(uint32_t x, uint32_t y, uint32_t steps) {
  node_t * n = calloc(1, sizeof(node_t));

  n->x = x;
  n->y = y;
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

node_t * q_get() {
  if (head != NULL) {
    q_size--;
    node_t * ret = head;
    head = head->next;
    return ret;
  }

  return NULL;
}

int q_empty() {
  return head == NULL;
}

void q_clear() {
     while(head != NULL) {
        node_t * tmp = q_get();
        free(tmp);
      }
}

char v[200][200];
char m[200][200];
int p[200][200];

int valid(int32_t x, int32_t y) {
  return m[x][y] != '#' && !v[x][y];
}

int BFS(int x, int y, int tx, int ty) {
  q_add(x, y, 0);

  while(!q_empty()) {
    node_t * n = q_get();

    if (n->x == tx && n->y == ty) {
      return n->steps;
    }

    if (valid(n->x, n->y+1)) {
      q_add(n->x, n->y+1, n->steps+1);
      v[n->x][n->y+1] = 1;
    }
    if (valid(n->x-1, n->y)) {
      q_add(n->x-1, n->y, n->steps+1);
      v[n->x-1][n->y] = 1;
    }
    if (valid(n->x, n->y-1)) {
      q_add(n->x, n->y-1, n->steps+1);
      v[n->x][n->y-1] = 1;
    }   
    if (valid(n->x+1, n->y)) {
      q_add(n->x+1, n->y, n->steps+1);
      v[n->x+1][n->y] = 1;
    }

    free(n);
  }

  return -1;
}

int get_x(char ch) {
  for(int i = 0; i < 200; i++)
    for(int j = 0; j < 200; j++) 
      if (m[i][j] == ch) return i;

  return -1;
}

int get_y(char ch) {
  for(int i = 0; i < 200; i++)
    for(int j = 0; j < 200; j++) 
      if (m[i][j] == ch) return j;

  return -1;
}

char z[200];
int my = 1000;

int MAX = 0;

void sp(int y, int s, int cnt) {
  z[y] = 1;

  if (cnt == MAX) {
    if (s < my) 
      my = s+p[y][0];

    z[y] = 0;
    return;
  }

  for(int j = 0; j < MAX + 1; j++) {
    if (!z[j] && p[y][j] > 0) {
      sp(j, s+p[y][j], cnt + 1);
    }
  }

  z[y] = 0;
}


int main(int argc, char ** argv) {
  int x1, y1, x2, y2, k = 0;

  while(fgets(m[k++], 1000, stdin)) {
    for(int i = 0; i < strlen(m[k-1]); i++) {
      int c = m[k-1][i] - '0';
      if (c > 0 && c < 9 ) {
        if (c > MAX) {
          MAX = c;
        }
      }
    }
  }

  for(char i = 0; i <= MAX - 1; i++) {
    for(char j = i+1; j <= MAX; j++) {
      x1 = get_x(i + '0');
      y1 = get_y(i + '0');
      x2 = get_x(j + '0');
      y2 = get_y(j + '0');

      memset(v, 0, 200 * 200 * sizeof(char));
      
      // clear the queue
      q_clear();

      int min = BFS(x1, y1, x2, y2);

      printf("From %d %d,%d to %d %d,%d - %d\n", i, x1, y1, j, x2, y2, min);

      p[i][j] = p[j][i] = min;
    }
  }

  // brute force and find the sum of the minimum in all pairs
  sp(0, 0, 0);

  printf("%d\n", my);

}
