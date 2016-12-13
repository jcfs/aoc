/* compile gcc -o p2 p2.c -Wall */
#include <stdio.h>
#include <stdint.h>

#define SIZE 50

uint32_t input = 1364, min = 50, count = 0;
uint8_t maze[SIZE][SIZE],  v[SIZE * SIZE];

uint8_t is_wall(uint8_t x, uint8_t y) {
  return __builtin_popcount(x * x + 3 * x + 2 * x * y + y + y*y + input) % 2;
}

// solve the problem recursivly (DFS)
void solve(uint8_t x, uint8_t y, uint8_t steps) {

  // if the current steps is greater than the desired min
  // we don't need to proceed any further
  if (steps > min) 
    return;

  maze[y][x] = 1;

  // check the visited matrix to see if this is a new location
  if (!v[y * SIZE + x]) v[y * SIZE + x] = 1 && ++count && printf("new cool place: %d\n", count);

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
