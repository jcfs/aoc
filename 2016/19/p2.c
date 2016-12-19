/* compile gcc -o p2 p2.c -Wall -O3 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct seat {
  uint32_t elf;
  struct seat * next;
  struct seat * prev;
} seat_t;

int main(int argc, char ** argv) {
  uint32_t table_size = 3001330;

  seat_t * head = calloc(table_size, sizeof(seat_t));
  seat_t * curr = head;

  for(int i = 0; i < table_size; i++, curr++) {
    curr->elf = i;
    curr->next = curr + 1;
    curr->next->prev  = curr; 
  }

  (curr-1)->next = head;
  head->prev = (curr-1);
  curr = head;

  for(seat_t * middle = head + table_size / 2; table_size > 1; curr = curr->next, table_size--) {
    // remove the current middle
    seat_t * p = middle->next;
    middle->prev->next = p;
    p->prev = middle->prev;
    middle = p;

    // dunno why this is like this... obversation...
    if ((table_size % 2)) 
      middle = middle->next;
  }

  printf("part 2: %d\n",curr->elf + 1);
}
