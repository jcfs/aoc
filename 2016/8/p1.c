/* compile gcc -o p1 p1.c -Wall */
/* solution for both part 1 and 2 */
#include <stdio.h>
#include <string.h>

#define ROWS      8
#define COLUMNS   50

int m[ROWS][COLUMNS];

// draw the rectangle
void draw_rect(int w, int h) {
  for(int i = 0; i < w; i++)
    for(int j = 0; j < h; j++)
      m[j][i] = 1;
}

// rotate row (r) right by k positions
void rotate_right(int r, int k) {
  for(int i = 0; i < k; i++) 
    for(int t = m[r][49], j = 49; j >= 0; j--) 
      m[r][j] = (!j) ? t : m[r][j-1]; 
}

// rotate column (c) down by k positions
void rotate_down(int c, int k) {
  for(int i = 0; i < k; i++) 
    for(int t = m[5][c], j = 5; j >= 0; j--) 
      m[j][c] = (!j) ? t : m[j-1][c];
}

int main(int argc, char ** argv) {
  int s = 0, x, y;
  char command[254];

  while(fgets(command, 254, stdin) != NULL) {
    if (sscanf(command, "rect %dx%d", &x, &y)) 
      draw_rect(x, y);
    else if (sscanf(command, "rotate row y=%d by %d", &x, &y))
      rotate_right(x, y);
    else if (sscanf(command, "rotate column x=%d by %d", &x, &y))
      rotate_down(x, y);
  }

  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLUMNS; j++)
      (m[i][j] && ++s) ? printf("#") : printf(" ");
    printf("\n");
  }

  printf("%d\n", s);
}
