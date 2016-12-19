/* compile gcc -o p1 p1.c -Wall -O3 */
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

  // create circular linked list
  seat_t * head = calloc(table_size, sizeof(seat_t));
  seat_t * curr = head;

  for(int i = 1; i <= table_size; i++, curr++) {
    curr->elf = i;
    curr->next = curr + 1;
    curr->next->prev  = curr; 
  }

  (curr-1)->next = head;
  head->prev = (curr-1);
  curr = head;

  for(seat_t * n = curr->next; table_size > 1; curr = curr->next, table_size--) {
    n = curr->next;
    // remove the current element
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }

  printf("part 1: %d\n", curr->elf);
}
