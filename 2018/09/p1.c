#include <stdio.h>
#include <stdlib.h>

typedef struct m {
  int v;
  struct m * next;
  struct m * prev;
} marble;

marble * root;

int scores[1000];

int main() {
  int players, marbles;
  int current_player;

  scanf("%d players; last marble is worth %d points\n", &players, &marbles);

  root = calloc(1, sizeof(marble));

  root->v = 0;
  root->next = root;
  root->prev = root;

  current_player = 1;
  for(int i = 1; i <= marbles; i++) {
    if (i % 23) {
      marble * t = root;
      t = t->next;
      marble * new = calloc(1, sizeof(marble));
      new->v = i;
      new->next = t->next;
      new->prev = t;
      t->next->prev = new;
      t->next = new;

      root = new;
    } else {
      scores[current_player] += i;
      marble * t = root;
      for(int k = 0; k < 7; k++) {
        t = t->prev;
      }

      root = t->next;
      t->next->prev = t->prev;
      t->prev->next = t->next;

      scores[current_player] += t->v;
    }

    current_player++;
    if (current_player > players)
      current_player = 1;
  }

  int m = 0;
  for(int i = 1; i <= players; i++) {
    if (scores[i] > m)
      m = scores[i];
  }

  printf("%d\n", m);
}
