#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

char city[1000][1000];

int get_next_dir(int current_dir, char move) {
 
 if (move == 'R') {
   if (current_dir == NORTH) return EAST;
   if (current_dir == EAST) return SOUTH;
   if (current_dir == SOUTH) return WEST;
   if (current_dir == WEST) return NORTH;
 } 

 if (move == 'L') {
   if (current_dir == NORTH) return WEST;
   if (current_dir == WEST) return SOUTH;
   if (current_dir == SOUTH) return EAST;
   if (current_dir == EAST) return NORTH;
 }
}

int main(int agrc, char ** argv) {

  int current_dir = NORTH;
  int x = 500, y = 500;
  int old_x = 500, old_y = 500;
  int i,j;
  char move;
  int distance;

  while(scanf("%c%d, ", &move, &distance) == 2) {
    current_dir = get_next_dir(current_dir, move);

    old_x = x;
    old_y = y;

    if (current_dir == NORTH) y += distance;
    if (current_dir == SOUTH) y -= distance;
    if (current_dir == EAST) x += distance;
    if (current_dir == WEST) x -= distance;

    printf("%d %d - (%d, %d)\n", current_dir, distance, x-500, y-500);

    if (old_x != x) {
      if (x > old_x) {
        for(i = old_x; i < x; i++) city[i][y] += 1;
      } else if (old_x > x) {
        for(i = x+1; i <= old_x; i++) city[i][y] += 1;
      }
    }
    
    if (old_y != y) {
      if (y > old_y) {
        for(i = old_y; i < y; i++) city[x][i] += 1;
      } else if (old_y > y) {
        for(i = y+1; i <= old_y; i++) city[x][i] += 1;
      }
    }

    for(i = 0; i < 1000; i++) {
      for(j = 0; j < 1000; j++) {
        if (city[i][j] > 1) { printf("->> %d\n", abs(i-500)+abs(j-500)); return 0; }
      }
    }
  } 
  
  return 0;
}
