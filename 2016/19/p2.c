#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct seat {
  uint32_t elf;
  uint32_t presents;
  struct seat * next_seat;
  struct seat * prev_seat;
} seat;

int table_size;


void print_table(seat * s, int n) {
  for(int i = 0; i < n; i++) {

    printf("elf %d has %d presents\n", s->elf + 1, s->presents);
    s = s->next_seat;
  }
}

int main(int argc, char ** argv) {
  int input = 3001330, index = 0;
  table_size = input;
  
  seat * head  = calloc(1, sizeof(seat));
  head->elf = 0;
  head->presents = 1;

  seat * last = head;
  for(int i = 1; i < input; i++) {
    seat * n = calloc(1, sizeof(seat));

    last->next_seat = n;
    n->elf = i;
    n->presents = 1;
    n->prev_seat = last;

    last = n;
  }

  last->next_seat = head;
  head->prev_seat = last;

  seat * current = head;  
  seat * act = head;
  while(1) {
    printf("%d\n", table_size);
    if (table_size == 1) break;
    int increment = table_size / 2;

    seat * last = current;
    while(increment) {
      last = current;
      current = current->next_seat;
      increment--;
    }

//    printf("elf %d will remove from elf %d - (the prev elf is %d)\n", act->elf + 1 , current->elf + 1, last->elf + 1);
    act->presents += current->presents;
    if (act->presents == input) {
      printf("%d %d\n",act->elf + 1, act->presents);
      exit(0);
    }

    last->next_seat = current->next_seat;
    // because we care;
    //free(current);
    table_size -= 1;
    act = act->next_seat;
    current = act;
  }

}
