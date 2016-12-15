#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define CITY_SIZE 1000
#define START_POS 500

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

char DIRS[4] = { NORTH, EAST, SOUTH, WEST };
char city[CITY_SIZE][CITY_SIZE];

int TURN_MATRIX[4][2] = {
  {0, 1}, 
  {1, 0}, 
  {0, -1}, 
  {-1, 0}
};

int get_next_dir(int current_dir, char move) {
 if (move == 'R') {
   return DIRS[(current_dir + 1) % 4];
 } else {
   return DIRS[(current_dir + 3) % 4];
 } 
}

void check_city(int x, int y) {
  if (city[x][y] > 1) {
    printf("%d\n", abs(x-START_POS)+abs(y-START_POS));
    exit(0);
  }
}

void fill_line(int begin_x, int end_x, int begin_y, int end_y) {
  int i;

  for(i = begin_x; (end_x > begin_x) ? (i < end_x) : (i > end_x); (end_x > begin_x) ? i++ : i--) {
      city[i][begin_y] += 1;
      check_city(i, begin_y);    
  }

  for(i = begin_y; (end_y > begin_y) ? (i < end_y) : (i > end_y); (end_y > begin_y) ? i++ : i--) {
      city[begin_x][i] += 1;
      check_city(begin_x, i);    
  }
}

int main(int agrc, char ** argv) {
  int current_dir = NORTH;
  int x = START_POS, y = START_POS;
  int ox = START_POS, oy = START_POS;
  char move;
  int distance;

  while(scanf("%c%d, ", &move, &distance) == 2) {
    current_dir = get_next_dir(current_dir, move);
    
    ox = x;
    oy = y;

    x += TURN_MATRIX[current_dir][0] * distance;
    y += TURN_MATRIX[current_dir][1] * distance;

    fill_line(ox, x, oy, y);
  } 

  printf("%d\n", abs(x-START_POS)+abs(y-START_POS));

  return 0;
}
