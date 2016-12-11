/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int floors[4][6] = {
  { 0,  1,  0,  2, 0, 10},
  { -1, 0,  0,  0, 0, 0},
  { 0,  0,  -2, 0, 0, 0},
  { 0,  0,  0,  0, 0, 0},
};

int state[400000][4][6];
int statesteps[400000] = {[0 ... 200000] = 10000};
int s = 0;


void copy_state(int ele, int steps) {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 6; j++)
      state[s][i][j] = floors[i][j];

  state[s][ele][5] = 10;
  statesteps[s] = steps;

  s++;
}

char is_prev_state(int steps) {
  int f = 0;
  for(int k = 0; k < s; k++) {
    f = 1;
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 6; j++)
        if (state[k][i][j] != floors[i][j]) f = 0;
    }
    if (f) {
      return statesteps[k] > f;
    }
  }

  return 0;
}
void print_map(int ele) {

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 5; j++) {
      if (j < 4) printf("% 3d ", floors[i][j]);
      else if (ele == i) printf(" E ");
    }
    printf("\n");
  }
  printf("--------------------\n");

}

char is_another_rtg(int n, int chip) {
  for (int i = 0; i < 4; i++) {
    if (floors[n][i] < 0 && chip * -1 != floors[n][i]) return 1;
  }

  return 0;
}

char own_rtg(int n, int chip) {
  for (int i = 0; i < 4; i++) {
    if (floors[n][i] < 0 && chip * -1 == floors[n][i]) return 1;
  }

  return 0;
}

char valid_floor(int n) {
  for(int i = 0; i < 4; i++) {
    if (floors[n][i] > 0 && is_another_rtg(n, floors[n][i]) && !own_rtg(n, floors[n][i])) return 0;
  }

  return 1;
}

char valid_board() {
  for(int i = 0; i < 4; i++) if (!valid_floor(i)) return 0;
  return 1;
}

char is_final() {
  for(int i = 0; i < 4; i++) if (!floors[3][i]) return 0;
  return 1;
}

int min = 10;

void move_up(int ele, int i) {
  floors[ele+1][i] = floors[ele][i];
  floors[ele][i] = 0;

  floors[ele+1][5] = 10;
  floors[ele][5] = 0;
}


void move_down(int ele, int i) {
  floors[ele-1][i] = floors[ele][i];
  floors[ele][i] = 0;

  floors[ele-1][5] = 10;
  floors[ele][5] = 0;
}

void solve(int ele, int steps) {

  if (steps > min) return;

  copy_state(ele, steps);
  print_map(ele);
  printf("min: %d curr_steps: %d\n", min, steps);

  if (is_final()) {
    min = (steps < min) ? steps : min;
    printf("FINALLLLLLL %d", min);
    return;
  }

  for(int i = 0; i < 4; i++) {
    for(int j = i+1; j < 4; j++) {
      int a = floors[ele][i];
      int b = floors[ele][j];

      if (ele < 3) {
        if (a) move_up(ele, i);
        if (b) move_up(ele, j);
        if (valid_board() && (a || b) && (!is_prev_state(steps+1))) {
          solve(ele + 1, steps + 1);
        }

        if (a) move_down(ele+1, i);
        if (b) move_down(ele+1, j);

      }

      if (ele > 0) {
        if (a) move_down(ele, i);
        if (b) move_down(ele, j);

        if (valid_board() && (a || b) && (!is_prev_state(steps+1))) {
          solve(ele - 1, steps+1);
        }

        if (a) move_up(ele-1, i);
        if (b) move_up(ele-1, j);

      }
    }
  }
}

int main(int argc, char ** argv) {

  for(int i = 0; i < 4; i++) {
    printf("floor %d is %d\n", i + 1, valid_floor(i));
  }

  solve(0, 0);
  printf("%d\n", min);
}
