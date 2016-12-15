#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define N_FLOORS 4
#define N_ELEMENTS 4

typedef struct state {
  int8_t elevator;
  uint32_t steps;

  int8_t floor_n[N_FLOORS];
  int8_t * floor[N_FLOORS];
} state;

state states[1];
state current_state;

// creates a new state
state * create_state(int8_t elevator, uint32_t steps, 
    int8_t * floor0, int8_t floor0_n, 
    int8_t * floor1, int8_t floor1_n, 
    int8_t * floor2, int8_t floor2_n, 
    int8_t * floor3, int8_t floor3_n) {

  state * s = (state *) calloc(1, sizeof(state));

  s->elevator = elevator;
  s->steps = steps;

  s->floor_n[0] = floor0_n;
  s->floor_n[1] = floor1_n;
  s->floor_n[2] = floor2_n;
  s->floor_n[3] = floor3_n;

  if (floor0_n > 0) {
    s->floor[0] = calloc(floor0_n, sizeof(int8_t));
    memcpy(s->floor[0], floor0, floor0_n * sizeof(int8_t));
  }

  if (floor1_n > 0) {
    s->floor[1] = calloc(floor1_n, sizeof(int8_t));
    memcpy(s->floor[1], floor1, floor1_n * sizeof(int8_t));
  }

  if (floor2_n > 0) {
    s->floor[2] = calloc(floor2_n, sizeof(int8_t));
    memcpy(s->floor[2], floor2, floor2_n * sizeof(int8_t));
  }

  if (floor3_n > 0) {
    s->floor[3] = calloc(floor3_n, sizeof(int8_t));
    memcpy(s->floor[3], floor2, floor2_n * sizeof(int8_t));
  }
  return s;
}

state * clone(state * r) {

  state * s = (state *) calloc(1, sizeof(state));

  s->elevator = r->elevator;
  s->steps = r->steps;

  for(int i = 0; i < N_FLOORS; i++) {
    s->floor_n[i] = r->floor_n[i];
    if (s->floor_n[i] > 0) {
      s->floor[i] = calloc(s->floor_n[i], sizeof(int8_t));
      memcpy(s->floor[i], r->floor[i], r->floor_n[i] * sizeof(int8_t));
    }
  }

  return s;

}

// free all the memory related to a state
void destroy_state(state * s) {
  if (s->floor[0] != NULL) free(s->floor[0]);
  if (s->floor[1] != NULL) free(s->floor[1]);
  if (s->floor[2] != NULL) free(s->floor[2]);
  if (s->floor[3] != NULL) free(s->floor[3]);

  free(s);
}

void print_state(state * s) {
  for(int i = 0; i < N_FLOORS; i++) {
    printf("F%d %c ", i, (s->elevator == i) ? 'E' : '-' );
    for(int j = 0; j < s->floor_n[i]; j++) {
      printf(" %d ", s->floor[i][j]);
    }
    printf("\n");
  }
  printf("------------------\n");
}

bool same_state(state * s1, state * s2) {
  if (s1->elevator != s2->elevator) return false;

  for(int i = 0; i < N_FLOORS; i++) {
    if (s1->floor_n[i] != s2->floor_n[i]) return false;
    for(int j = 0; j < s1->floor_n[i]; j++) {
      if (s1->floor[i][j] != s2->floor[i][j]) return false;
    }
  }

  return true;
}

int cmp (const void * a, const void * b) {
  return ( *(int8_t*)a - *(int8_t*)b  );
}

// we reduce the state so we can have similar states
state * reduce_state(state * r) {
  int8_t current_chip = 1;

  state * s = clone(r);

  for(int i = 0; i < N_FLOORS; i++)
    qsort(s->floor[i], s->floor_n[i], sizeof(int8_t), cmp);

  for(int i = 0; i < N_FLOORS; i++) {
    for(int j = 0; j < s->floor_n[i]; j++) {
      int8_t item = s->floor[i][j];

      // horrible hack
      if (item > 0 && item < 100 ) {
        for(int n = 0; n < N_FLOORS; n++)
          for(int k = 0; k < s->floor_n[n]; k++)
            if (s->floor[n][k] == item * -1) 
              s->floor[n][k] = current_chip * -1 - 100;
        s->floor[i][j] = current_chip + 100;
        current_chip++;
      }
    }
  }

  for(int i = 0; i < N_FLOORS; i++)
    for(int j = 0; j < s->floor_n[i]; j++) {
      if (s->floor[i][j] > 100) 
        s->floor[i][j] -= 100;
      else if (s->floor[i][j] < 100) 
        s->floor[i][j] += 100;
    }
  return s;
}

// checks if the arg state is the final state.
// the final state is the state with all the elements (microchips and generators) on the top floor
bool is_final_state(state * s) {
  // if the last floor is not full of elements it is not the final state
  return s->floor_n[3] == N_ELEMENTS ? true : false;
}

bool has_unpaired_chip(int8_t * floor, uint8_t size) {
  for(int i = 0; i < size; i++) {
    if (floor[i] > 0) {
      bool paired = false;
      for(int j = 0; j < size; j++) {
        if (floor[j] == floor[i] * -1) 
          paired = true;
      }
    
      if (!paired) 
        return true;
    }
  }

  return false;
}

bool has_generator(int8_t * floor, uint8_t size) {
  for(int i = 0; i < size; i++) {
    if (floor[i] < 0) return true;
  }

  return false;
}

bool is_valid_state(state * s) {
  // check all the floors to see if they are all in a valid state
  // meaning that a generator cannot be on the same floor of an unpaired chip

  for(int i = 0; i < N_FLOORS; i++) {
    for(int j = 0; j < s->floor_n[i]; j++) {
      if (has_unpaired_chip(s->floor[i], s->floor_n[i]) && has_generator(s->floor[i], s->floor_n[i])) 
        return false;
    }
  }

  return true;
}

// item moves up
void move_up(state * s, int8_t item1, int8_t item2) {
  uint8_t elevator = s->elevator;

  for(int i = 0; i < s->floor_n[elevator]; i++) {
    if (s->floor[elevator][i] == item1 || s->floor[elevator][i] == item2)
      s->floor[elevator][i] = 0;
  }

  // we decrement the item count that we removed from the floor
  // and allocate a new floor
  int8_t * new_floor;
  int8_t i_count = (item1 != 0) ? (item2 != 0) ? 2 : 1 : 0;
  if (s->floor_n[elevator] - i_count > 0) {
    new_floor = calloc(s->floor_n[elevator] - i_count, sizeof(int8_t));
    for(int i = 0, j = 0; i < s->floor_n[elevator]; i++) {
      if (s->floor[elevator][i])
        new_floor[j++] = s->floor[elevator][i];
    }
  } 
  s->floor_n[elevator] -= i_count; 
  free(s->floor[elevator]);
  s->floor[elevator] = new_floor;

  // we increase the elevator
  s->elevator++;


}

int main(int argc, char ** argv) {

}
