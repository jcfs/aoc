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

      grid[j][i] = level;
    }
  }

  long area;
  unsigned min = 0;
  int x_min = 0;
  int y_min;
  int z_min;

  for(int z = 1; z <= 300;  z++) {
    for(int y = z - 1; y <= 300 - z - 2; y++) {
      for(int x = z - 1; x <= 300 - z - 2; x++) {
        area = 0;

        for(int i = 0; i < z; i++)
          for(int j = 0; j < z; j++)
            area += grid[y+i][x+j];

        if (area > min) {
          min = area;
          x_min = y-1;
          y_min = x-1;
          z_min=z;
        }
      }
    }
  }

  printf("%d,%d,%d\n", x_min, y_min, z_min);

}
