/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>
#include <stdint.h>

#define SIZE 255

uint32_t input = 1364, min = -1;
uint8_t maze[SIZE][SIZE], fx = 39, fy = 31;

uint8_t is_wall(uint8_t x, uint8_t y) {
  return __builtin_popcount(x * x + 3 * x + 2 * x * y + y + y*y + input) % 2;
}

// solve the problem recursivly (DFS)
void solve(uint8_t x, uint8_t y, uint8_t steps) {
  // if the current steps is greater than the desired min
  // we don't need to proceed any further
  if (steps >= min) 
    return;

  // check if we are at the target position and update the minimum steps to reach it
  (y == fy && x == fx) ? (min = steps) && printf("Wow... new minimum: %u\n", min) : 0;

  maze[y][x] = 1;

  // try all the possible moves
  if (x < SIZE && !maze[y][x+1]) solve(x+1, y, steps+1);
  if (y < SIZE && !maze[y+1][x]) solve(x, y+1, steps+1);
  if (x > 0 && !maze[y][x-1]) solve(x-1, y, steps+1);
  if (y > 0 && !maze[y-1][x]) solve(x, y-1, steps+1);

  maze[y][x] = 0;

  return;
}

int main(int argc, char ** argv) {
  for(int x = 0; x < SIZE; x++) 
    for(int y = 0; y < SIZE; y++) 
      maze[y][x] = is_wall(y, x);

  solve(1, 1, 0);
}
