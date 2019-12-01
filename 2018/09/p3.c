#include <stdio.h>
#include <stdlib.h>

typedef struct m {
  int v;
  struct m * next;
  struct m * prev;
} marble;

long scores[1000];

int main() {
  int players, marbles;
  int current_player = 0; 

  marble * pool, * current, * new, * tmp;

  marbles = 50000000;

  pool = calloc(marbles, sizeof(marble));
  current = pool;
  current->next = current;
  current->prev = current;
  current->v = 0;
 
  for(int i = 1; i <= 50000000; i++) {
    for(int k = 0;k < 382; k++) current = current->next;

    printf("%d\n", i);
    pool[i].next = current->next;
    pool[i].prev = current;
    pool[i].v = i;
    current->next->prev = &pool[i];
    current->next = &pool[i];
    current = &pool[i];
  }
    
  printf("%d\n", pool[0].next->v);
}

