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

  scanf("%d players; last marble is worth %d points\n", &players, &marbles);
  marbles *= 100;

  pool = calloc(marbles, sizeof(marble));
  current = pool;
  current->next = current;
  current->prev = current;

  for(int i = 1; i <= marbles; i++) {
    if (i % 23) {
      tmp = current;
      tmp = tmp->next;
      new = pool+i;
      new->v = i;
      new->next = tmp->next;
      new->prev = tmp;
      tmp->next->prev = new;
      tmp->next = new;
      current = new;
    } else {
      tmp = current;

      for(int k = 0; k < 7; k++, tmp = tmp->prev);
      current = tmp->next;
      tmp->next->prev = tmp->prev;
      tmp->prev->next = tmp->next;

      scores[current_player] += tmp->v + i;
    }

    current_player = (current_player + 1) % players;
  }

  long m = 0;
  for(int i = 0; i < players; i++) {
    if (scores[i] > m)
      m = scores[i];
  }

  printf("%ld\n", m);
}

