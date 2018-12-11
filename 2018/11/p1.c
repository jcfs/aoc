#include <stdio.h>
#include <stdlib.h>

long grid[301][301];

int main() {
  int s;
  scanf("%d\n", &s);

  for(int i = 1; i <= 300; i++) {
    for(int j = 1; j <= 300; j++) {
      long long rack_id = j + 10;
      long long level = rack_id * i;
      level += s;
      level *= rack_id;

      level = (level/100) % 100;
      if (level >= 10)
        level %= 10;
      level -= 5;

      grid[i][j] = level + grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1];
    }
  }

  long area;
  int min = -1000000;
  int x_min = 0;
  int y_min;
  int z_min;

  for(int z = 3; z <= 3;  z++) {
    for(int y = z; y <= 300; y++) {
      for(int x = z; x <= 300; x++) {
        area = grid[x][y] - grid[x-z][y] - grid[x][y-z] + grid[x-z][y-z];

        if (area > min) {
          min = area;
          x_min = y - z + 1;
          y_min = x - z + 1;
          z_min=z;
        }
      }
    }
  }

  printf("%d,%d,%d %d\n", x_min, y_min, z_min, min);

}
