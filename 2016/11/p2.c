/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define FLOORS 4
#define SPOTS 12

int floors1[FLOORS][6] = {
  { 0,  1,  0,  2, 0, 10},
  { -1, 0,  0,  0, 0, 0},
  { 0,  0,  -2, 0, 0, 0},
  { 0,  0,  0,  0, 0, 0},
};

int floors[4][SPOTS] = {
  { -1,  1,   0,   0,  0,  0, 0, 0, 0, 0, 0, 10},
  {  0,  0,  -2,  -3, -4, -5, 0, 0, 0, 0, 0, 0},
  {  0,  0,   0,   0,  0,  0, 2, 3, 4, 5, 0, 0},
  {  0,  0,   0,   0,  0,  0, 0, 0, 0, 0, 0, 0},
};


int state[500000][FLOORS][SPOTS];
int statesteps[500000] = {[0 ... 200000] = 10000};
int s = 0;


void copy_state(int ele, int steps) {
  for(int i = 0; i < FLOORS; i++)
    for(int j = 0; j < SPOTS; j++)
      state[s][i][j] = floors[i][j];

  state[s][ele][SPOTS-1] = 10;
  statesteps[s] = steps;

  s++;
}

char is_prev_state(int steps) {
  int f = 0;
  for(int k = 0; k < s; k++) {
    f = 1;
    for(int i = 0; i < FLOORS; i++) {
      for(int j = 0; j < SPOTS-2; j++)
        if (state[k][i][j] != floors[i][j]) f = 0;
    }
    if (f) {
      if (statesteps[k] > steps) {
        printf("REPETIDO E PIOR %d %d %d\n", k, statesteps[k], steps);
        print_map(state[k], 0);
        print_map(floors, 0);
        return 1;
      } 
      return statesteps[k] > steps;
    }
  }

  return 0;
}
void print_map(int ** f, int ele) {

  for(int i = 0; i < FLOORS; i++) {
    for(int j = 0; j < SPOTS-1; j++) {
      if (j < SPOTS - 2) printf("% 3d ", f[i][j]);
      else if (ele == i) printf(" E ");
    }
    printf("\n");
  }
  printf("--------------------\n");

}

char is_another_rtg(int n, int chip) {
  for (int i = 0; i < FLOORS; i++) {
    if (floors[n][i] < 0 && chip * -1 != floors[n][i]) return 1;
  }

  return 0;
}

char own_rtg(int n, int chip) {
  for (int i = 0; i < FLOORS; i++) {
    if (floors[n][i] < 0 && chip * -1 == floors[n][i]) return 1;
  }

  return 0;
}

char valid_floor(int n) {
  for(int i = 0; i < SPOTS-2; i++) {
    if (floors[n][i] > 0 && is_another_rtg(n, floors[n][i]) && !own_rtg(n, floors[n][i])) return 0;
  }

  return 1;
}

char valid_board() {
  for(int i = 0; i < FLOORS; i++) if (!valid_floor(i)) return 0;
  return 1;
}

char is_final() {
  for(int i = 0; i < FLOORS; i++) if (!floors[3][i]) return 0;
  return 1;
}

char * get_floor_n(int ele) {

  int c = 0;
  for(int i = 0; i < FLOORS; i++) if (floors[ele][i]) c++;
  char * ret = (char *) calloc(c + 1, sizeof(char));
  for(int i = 0, j = 0; i < FLOORS; i++) if (floors[ele][i]) ret[j++] = floors[ele][i];

  return ret;
}

int min = 34;

void move_up(int ele, int a) {
  int i = 0;

  for(i = 0; i < SPOTS-2; i++) if (floors[ele][i] == a) break;

  floors[ele+1][i] = floors[ele][i];
  floors[ele][i] = 0;

  floors[ele+1][SPOTS-1] = 10;
  floors[ele][SPOTS-1] = 0;
}


void move_down(int ele, int a) {
  int i = 0;
  for(i = 0; i < SPOTS-2; i++) if (floors[ele][i] == a) break;

  floors[ele-1][i] = floors[ele][i];
  floors[ele][i] = 0;

  floors[ele-1][SPOTS-1] = 10;
  floors[ele][SPOTS-1] = 0;
}

void solve(int ele, int steps) {

  if (steps > min) return;

  copy_state(ele, steps);

  ////printf("min: %d curr_steps: %d\n", min, steps);

  if (is_final()) {
    min = (steps < min) ? steps : min;
    print_map(&floors, ele);
    return;
  }

  char * floors_n = get_floor_n(ele);

  for(int i = 0; floors_n[i]; i++) {
    for(int j = i+1; ; j++) {
      int a = floors_n[i];
      int b = floors_n[j];

      if (ele < 3) {
        if (a) move_up(ele, a);
        if (b) move_up(ele, b);

        if (valid_board() && (a || b) && (!is_prev_state(steps+1))) {
          solve(ele + 1, steps + 1);
        }

        if (a) move_down(ele+1, a);
        if (b) move_down(ele+1, b);

      }

      if (ele > 0) {
        if (a) move_down(ele, a);
        if (b) move_down(ele, b);

        if (valid_board() && (a || b) && (!is_prev_state(steps+1))) {
          solve(ele - 1, steps+1);
        }

        if (a) move_up(ele-1, a);
        if (b) move_up(ele-1, b);

      }

      if (!floors_n[j]) break;
    }
  }
}

int main(int argc, char ** argv) {

  for(int i = 0; i < FLOORS; i++) {
    printf("floor %d is %d\n", i + 1, valid_floor(i));
  }

  solve(0, 0);
  printf("%d\n", min);
}
