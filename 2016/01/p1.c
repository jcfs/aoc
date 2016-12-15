#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

char DIRS[4] = { NORTH, EAST, SOUTH, WEST };
int TURN_MATRIX[4][2] = {{0, 1}, {1,0}, {0, -1}, {-1, 0}};

int get_next_dir(int current_dir, char move) {
 if (move == 'R') {
   return DIRS[(current_dir + 1) % 4];
 } else {
   return DIRS[(current_dir + 3) % 4];
 } 
}

int main(int agrc, char ** argv) {
  int current_dir = NORTH;
  int x = 0, y = 0;
  char move;
  int distance;

  while(scanf("%c%d, ", &move, &distance) == 2) {
    current_dir = get_next_dir(current_dir, move);
    x += TURN_MATRIX[current_dir][0] * distance;
    y += TURN_MATRIX[current_dir][1] * distance;
  } 

  printf("%d\n", abs(x)+abs(y));

  return 0;
}
