/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>
#include <stdint.h>

#define is_between(x, a, b) x >= a && x <= b
#define SIZE 255

uint32_t input = 1364, min = -1;
uint8_t maze[SIZE][SIZE], fx = 31, fy = 39;
uint8_t moves[4][2] = {
  {1, 0}, 
  {0, 1}, 
  {0, -1}, 
  {-1, 0}
};

// solve the problem recursivly (DFS)
void solve(uint8_t x, uint8_t y, uint8_t steps) {
  // if the current steps is greater than the desired min
  // we don't need to proceed any further
  if (steps >= min) 
    return;

  // check if we are at the target position and update the minimum steps to reach it
  (y == fy && x == fx) ? (min = steps) && printf("Wow... new minimum: %u\n", min) : 0;

  maze[x][y] = 1;

  // for every possible move we check if it is a valid move
  // and try it
  for(uint8_t i = 0; i < 4; i++) {
    uint8_t xi = x + moves[i][0];
    uint8_t yi = y + moves[i][1];

    if (is_between(xi, 0, SIZE - 1) && is_between(yi, 0, SIZE - 1) && !maze[xi][yi]) 
      solve(xi, yi, steps+1);
  }

  maze[x][y] = 0;

  return;
}

int main(int argc, char ** argv) {
  for(uint8_t x = 0; x < SIZE; x++) 
    for(uint8_t y = 0; y < SIZE; y++) 
      // check if it is a wall
      maze[x][y] = __builtin_popcount(x * x + 3 * x + 2 * x * y + y + y*y + input) % 2;

  solve(1, 1, 0);
}
